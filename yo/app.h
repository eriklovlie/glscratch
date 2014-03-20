#pragma once

#include "common.h"

class App {
public:
    App();
    virtual ~App();

    void init();
    void render();

private:
    uint32_t vbo;
};
