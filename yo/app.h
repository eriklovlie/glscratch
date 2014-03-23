#pragma once

#include "common.h"

class App {
public:
    App();
    virtual ~App();

    void init();
    void destroy();
    void render();

private:
    void init_vbo();
    void init_prog();
    std::string read_text_file( const char * path );
    uint32_t compile_shader( const char * path, GLenum shader_type );
    uint32_t load_prog( const char * vert_path, const char * geom_path, const char * frag_path );

    uint32_t vao;
    uint32_t vbo;
    uint32_t prog;
    uint32_t pos_attr;
};
