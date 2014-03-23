#include "app.h"
#include <fstream>
#include <vector>

App::App(){
    // NOTE: only do simple initialization here, no GL calls or anything.
}

App::~App(){
}

void App::init(){
    init_prog();
    init_vbo();
}

void App::destroy(){
    // TODO
}

void App::render(){
    glClearColor(0.1, 0.1, 0.1, 0.1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glUseProgram(prog);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES_ADJACENCY, 0, 6 * 2);
}

void App::init_vbo(){
    check_gl_error();

    pos_attr = glGetAttribLocation(prog, "in_Position");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float a = 0.4f;
    float w = 1.0f;

    float vertices[] = {
        -a, +a, 0, w,  // 0 - adjacent 0
        -a, +a, 0, w,  // 1 - leading
        +a, +a, 0, w,  // 2
        -a, 0, 0, w,   // 3 - adjacent

        +a, +a, 0, w,  // 0 - adjacent
        -a, 0, 0, w,   // 1 - leading
        +a, 0, 0, w,   // 2
        -a, -a, 0, w,  // 3 - adjacent

        +a, 0, 0, w,   // 0 - adjacent
        -a, -a, 0, w,  // 1 - leading
        +a, -a, 0, w,  // 2
        +a, -a, 0, w,  // 3 - adjacent
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(pos_attr, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(pos_attr);

    check_gl_error();
}

void App::init_prog(){
    prog = load_prog("glsl/solid.vert.glsl", "glsl/solid.geom.glsl", "glsl/solid.frag.glsl");
}

uint32_t App::load_prog( const char * vert_path, const char * geom_path, const char * frag_path ){
    uint32_t vert = compile_shader( vert_path, GL_VERTEX_SHADER );
    uint32_t geom = compile_shader( geom_path, GL_GEOMETRY_SHADER );
    uint32_t frag = compile_shader( frag_path, GL_FRAGMENT_SHADER );

    uint32_t prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, geom);
    glAttachShader(prog, frag);
    glLinkProgram(prog);

    GLint isLinked = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE){
        GLint maxLength = 0;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(prog, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(prog);
        glDeleteShader(vert);
        glDeleteShader(frag);

        std::cerr << "Linking of program failed." << std::endl;
        std::cerr<< "Vertex shader: " << vert_path << std::endl;
        std::cerr << "Fragment shader: " << frag_path << std::endl;
        std::cerr << "Error log: " << (char*)&infoLog[0] << std::endl;

        exit(1);
    }

    //Always detach shaders after a successful link.
    glDetachShader(prog, vert);
    glDetachShader(prog, geom);
    glDetachShader(prog, frag);
    return prog;
}

uint32_t App::compile_shader( const char * path, uint32_t shader_type ){
    uint32_t shader = glCreateShader(shader_type);
    std::string shader_text = read_text_file( path );
    const char * text_ptr = shader_text.c_str();
    glShaderSource(shader, 1, (const GLchar**)&text_ptr, 0);
    glCompileShader(shader);

    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<char> errorLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

    std::cerr << "Shader compilation log ---------------" << std::endl;
    std::cerr << "Shader path: " << path << std::endl;
    std::cerr << "Error log: " << (char*)&errorLog[0] << std::endl;

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if ( success == GL_FALSE ){
        std::cerr << "Compilation of shader failed." << std::endl;
        glDeleteShader(shader);
        exit(1);
    }else{
        std::cerr << "Compilation succeeded." << std::endl;
    }
    return shader;
}

std::string App::read_text_file( const char * path ){
    std::string contents;
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (in){
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
    }
    return contents;
}
