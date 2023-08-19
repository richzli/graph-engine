#pragma once

#include "component.hpp"

class rect : public component {
public:
    rect(glm::vec3 position, float length, float width, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
    rect(glm::vec2 pos, float length, float width);
    
protected:
    float length, width;

    void init_vertices() override;
};