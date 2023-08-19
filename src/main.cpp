#include "common.hpp"
#include "app.hpp"

config _config;
std::unique_ptr<app> _app;

int main(int argc, char * argv[]) {
    _config = { 1600, 900 };
    _app = std::make_unique<app>();

    _app->get_active_scene()->add_component(
        std::make_shared<rect>(glm::vec2(800, 450), 50, 50)
    );

    while (!glfwWindowShouldClose(_app->get_window())) {
        _app->render();

        glfwPollEvents();
        glfwSwapBuffers(_app->get_window());
    }

    return 0;
}