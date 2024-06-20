#include "common.hpp"
#include "settings.hpp"
#include "app.hpp"

config _config;
component_defaults _component_defaults;
app * _app;

int main(int argc, char * argv[]) {
    _config = { 1600, 900 };
    _app = &(app::get_instance());

    for (int i = 0; i < 5; ++i) {
        _app->get_active_scene().get_graph()->add_node();
        for (int j = 0; j < i; ++j) {
            _app->get_active_scene().get_graph()->add_edge(i, j);
        }
    }

    while (!glfwWindowShouldClose(_app->get_window())) {
        _app->render();

        glfwPollEvents();
        glfwSwapBuffers(_app->get_window());
        glFinish();
    }

    return 0;
}