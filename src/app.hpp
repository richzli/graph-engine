#pragma once

#include "common.hpp"
#include "engine/scene.hpp"

class app {
public:
    static app & get_instance();

    app(app const &) = delete;
    void operator=(app const &) = delete;

    static GLFWwindow * get_window();
    static std::shared_ptr<scene> get_active_scene();

    void render();
private:
    app();
    ~app();

    GLFWwindow * window;

    std::shared_ptr<scene> active_scene;

    void init_opengl();

    static void framebuffer_size_callback(GLFWwindow * window, const int width, const int height);
    static void window_refresh_callback(GLFWwindow * window);
};

extern app * _app;