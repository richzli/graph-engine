#include "core.hpp"

// shader initialization has to happen after glfw initialization
// so can't initialize these directly in the class source files; this is just a hack
void init_shaders() {
    circle::_shader = std::make_shared<shader>("basic", "circle");
    line::_shader = std::make_shared<shader>("basic", "basic");
}