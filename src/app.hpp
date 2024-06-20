#pragma once

#include "common.hpp"
#include "settings.hpp"
#include "engine/scene.hpp"

class app {
public:
    static app & get_instance();

    app(app const &) = delete;
    void operator=(app const &) = delete;

    static GLFWwindow * get_window();
    static scene & get_active_scene();

    void render();
private:
    app();
    ~app();

    GLFWwindow * window;

    std::shared_ptr<scene> active_scene;

    glm::vec2 last_cursor_pos;
    std::optional<std::chrono::time_point<std::chrono::steady_clock>> mouse_button_left_down;

    void init_opengl();
    static glm::vec2 get_mouse_pos();

    static void framebuffer_size_callback(GLFWwindow * window, const int width, const int height);
    static void window_refresh_callback(GLFWwindow * window);
    static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
};

extern app * _app;