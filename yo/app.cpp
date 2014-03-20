#include "app.h"

App::App(){
    // NOTE: only do simple initialization here, no GL calls or anything.
}

App::~App(){
}

void App::init(){
    uint32_t bongo = 42;
    printf("VBO before id = %d\n", bongo);
    printf("func = %p\n", (void*)glGenBuffers);
    glGenBuffers(1, &bongo);
    printf("VBO after id = %d\n", bongo);

//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    float vertices[] = {1.0f, 1.0f, 1.0f};
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void App::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// TODO
}
