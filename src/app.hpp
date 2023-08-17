#pragma once

#include "common.hpp"

class app {
public:
    app();
    ~app();

    GLFWwindow* get_window() const;
private:
    GLFWwindow * window;

    void init_opengl();

    static void framebuffer_size_callback(GLFWwindow* window, const int width, const int height);
};

extern std::unique_ptr<app> _app;