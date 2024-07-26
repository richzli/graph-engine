#include "core.hpp"

// shader initialization has to happen after glfw initialization
// so can't initialize these directly in the class source files; this is just a hack
void init_shaders() {
    circle::_shader = std::make_shared<shader>("node", "circle");
    line::_shader = std::make_shared<shader>("edge", "basic");
}

// same deal with these
void init_component_defaults() {
    _component_defaults = {
        std::make_shared<circle>(glm::vec2(0, 0), 20),
        std::make_shared<arrow>(glm::vec2(0, 0), glm::vec2(0, 0), 10.0f),
        std::make_shared<line>(glm::vec2(0, 0), glm::vec2(0, 0), 10.0f)
    };
}