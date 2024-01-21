#include "common.hpp"
#include "app.hpp"

config _config;
app * _app;

int main(int argc, char * argv[]) {
    _config = { 1600, 900 };
    _app = &(app::get_instance());

    _app->get_active_scene()->add_component(
        std::make_shared<circle>(glm::vec2(800, 450), 50)
    );
    
    _app->get_active_scene()->add_component(
        std::make_shared<arrow>(glm::vec2(200, 200), glm::vec2(400, 400), 10.0f)
    );

    while (!glfwWindowShouldClose(_app->get_window())) {
        _app->render();

        glfwPollEvents();
        glfwSwapBuffers(_app->get_window());
        glFinish();
    }

    return 0;
}