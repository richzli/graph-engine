#pragma once

#include "../components/core.hpp"
#include "render/shader.hpp"

class scene {
public:
    scene();

    void set_origin(glm::vec2 origin);
    void set_scale(glm::vec2 scale);

    void add_component(std::shared_ptr<component> obj);

    void draw();
private:
    glm::vec2 origin;
    glm::vec2 scale;

    std::vector<std::shared_ptr<component>> objects;
};