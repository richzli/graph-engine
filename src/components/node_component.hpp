#pragma once

#include "component.hpp"

class node_component : public component {
public:
    node_component();
    node_component(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color);
    node_component(const node_component & nc);

    glm::vec3 get_position() const;
    glm::vec3 get_rotation() const;
    glm::vec3 get_scale() const;
    std::vector<glm::vec2> get_vertices() const;
    glm::mat4 get_model_matrix() const;

    void set_position(glm::vec3 position);
    void set_rotation(glm::vec3 rotation);
    void set_scale(glm::vec3 scale);
protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 model;
    
    void update_model_matrix();
};