#include "app.hpp"

app & app::get_instance() {
    static app instance;
    return instance;
}

app::app() {
    init_opengl();
    init_imgui();

    active_scene = std::make_shared<scene>();
    mouse_button_left_down = std::nullopt;
}

app::~app() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow * app::get_window() {
	return get_instance().window;
}

scene & app::get_active_scene() {
    return *(get_instance().active_scene);
}

void app::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    active_scene->draw();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void app::init_opengl() {
    if (!glfwInit()) {
        throw std::runtime_error("failed to initialize glfw");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    ::init_shaders();
    ::init_component_defaults();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void app::init_imgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}   

glm::vec2 app::get_mouse_pos() {
    double x, y;
    glfwGetCursorPos(get_instance().window, &x, &y);
    return glm::vec2(x, y);
}

/* CALLBACKS */

void app::framebuffer_size_callback(GLFWwindow * window, const int width, const int height) {
	glViewport(0, 0, width, height);
	_config.width = width;
	_config.height = height;

    get_instance().active_scene->set_size(glm::vec2(width, height));
}

void app::window_refresh_callback(GLFWwindow * window) {
    get_instance().render();
    glfwSwapBuffers(window);
    glFinish();
}

void app::cursor_position_callback(GLFWwindow * window, double xpos, double ypos) {
    glm::vec2 current_cursor_pos = glm::vec2(xpos, ypos);

    if (get_instance().mouse_button_left_down != std::nullopt) {
        get_instance().active_scene->drag(current_cursor_pos - get_instance().last_cursor_pos);
    }

    get_instance().last_cursor_pos = current_cursor_pos;
}

void app::mouse_button_callback(GLFWwindow * window, int button, int action, int mods) {
    ImGuiIO & io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, action == GLFW_PRESS);

    if (!io.WantCaptureMouse) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                get_instance().mouse_button_left_down = std::chrono::steady_clock::now();
                get_instance().active_scene->select(get_mouse_pos());
            } else if (action == GLFW_RELEASE) {
                get_instance().mouse_button_left_down = std::nullopt;
                get_instance().active_scene->deselect();
            }
        }
    } else {
        get_instance().mouse_button_left_down = std::nullopt;
        get_instance().active_scene->deselect();
    }
}