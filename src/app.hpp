#pragma once

#include "common.hpp"
#include "scene/scene.hpp"

class app {
public:
    app();
    ~app();

    GLFWwindow * get_window() const;
    std::shared_ptr<scene> get_active_scene() const;

    void render();
private:
    GLFWwindow * window;

    std::shared_ptr<scene> active_scene;

    void init_opengl();

    static void framebuffer_size_callback(GLFWwindow * window, const int width, const int height);
};

extern std::unique_ptr<app> _app;