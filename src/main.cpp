#include "common.hpp"
#include "app.hpp"

int main(int argc, char * argv[]) {
    _config = { 1600, 900 };
    _app = std::make_unique<app>();

    while (!glfwWindowShouldClose(_app->get_window())) {
        glfwSwapBuffers(_app->get_window());
        glfwPollEvents();
    }

    return 0;
}