#include "app.hpp"

app::app() {
    init_opengl();
    active_scene = std::make_shared<scene>();
}

app::~app() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow * app::get_window() const {
	return window;
}

std::shared_ptr<scene> app::get_active_scene() const {
    return active_scene;
}

void app::render() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    active_scene->draw();
}

void app::init_opengl() {
    if (!glfwInit()) {
        throw std::runtime_error("failed to initialize glfw");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(_config.width, _config.height, "graph engine", nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("failed to create glfw window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("failed to initialize glad");
    }

    glViewport(0, 0, _config.width, _config.height);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void app::framebuffer_size_callback(GLFWwindow * window, const int width, const int height) {
	glViewport(0, 0, width, height);
	_config.width = width;
	_config.height = height;
}