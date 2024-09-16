#include "core.hpp"

// shader initialization has to happen after glfw initialization
// so can't initialize these directly in the class source files; this is just a hack
void init_shaders() {
    circle::_shader = std::make_shared<shader>("node", "circle");
    line::_shader = std::make_shared<shader>("edge", "basic");
}

// same deal with these
void init_component_defaults() {
    _component_defaults._node = 
        std::make_shared<circle>(glm::vec2(0, 0), 20);
    _component_defaults._edge_directed =
        std::make_shared<arrow>(glm::vec2(0, 0), glm::vec2(0, 0), 10.0f);
    _component_defaults._edge_undirected = 
        std::make_shared<line>(glm::vec2(0, 0), glm::vec2(0, 0), 10.0f);
}

void init_animation_defaults() {
    _animation_defaults.node_on_hover = std::make_shared<circle>(ZERO2, 0.0f);
    _animation_defaults.node_on_hover->scale[BASE] = std::make_shared<tween<glm::vec3>>(
        [](double t) {
            return ONE3 * (1.0f + 0.1f * ((float) t));
        },
        easing::linear(),
        0.15
    );
    _animation_defaults.node_on_hover->scale[BASE]->active = true;

    _animation_defaults.node_on_unhover = std::make_shared<circle>(ZERO2, 0.0f);
    _animation_defaults.node_on_unhover->scale[BASE] = std::make_shared<tween<glm::vec3>>(
        [](double t) {
            return ONE3 * (1.1f - 0.1f * ((float) t));
        },
        easing::linear(),
        0.15
    );
    _animation_defaults.node_on_unhover->scale[BASE]->active = true;
}