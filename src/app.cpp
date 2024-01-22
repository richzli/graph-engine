#include "app.hpp"

app & app::get_instance() {
    static app instance;
    return instance;
}

app::app() {
    init_opengl();
    active_scene = std::make_shared<scene>();
}

app::~app() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow * app::get_window() {
	return get_instance().window;
}

std::shared_ptr<scene> app::get_active_scene() {
    return get_instance().active_scene;
}

void app::render() {
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

    glfwSetWindowRefreshCallback(window, window_refresh_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    ::init_shaders();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void app::framebuffer_size_callback(GLFWwindow * window, const int width, const int height) {
	glViewport(0, 0, width, height);
	_config.width = width;
	_config.height = height;

    get_instance().active_scene->set_scale(glm::vec2(width, height));
}

void app::window_refresh_callback(GLFWwindow * window) {
    get_instance().render();
    glfwSwapBuffers(window);
    glFinish();
}