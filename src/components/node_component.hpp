#pragma once

#include "component.hpp"

class node_component : public component {
public:
    node_component(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
    node_component();

    glm::vec3 get_position() const;
    glm::vec3 get_rotation() const;
    glm::vec3 get_scale() const;
    glm::vec3 get_color() const;
    std::vector<glm::vec2> get_vertices() const;
    glm::mat4 get_model_matrix() const;

    void set_position(glm::vec3 position);
    void set_rotation(glm::vec3 rotation);
    void set_scale(glm::vec3 scale);
    void set_color(glm::vec3 color);
protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 color;
};