#pragma once

#include "component.hpp"

class node_component : public component {
public:
    node_component();
    node_component(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 offset, glm::vec4 color);
    node_component(const node_component & nc);

    glm::vec3 get_position();
    glm::vec3 get_rotation();
    glm::vec3 get_scale();
    std::vector<glm::vec3> get_vertices();
    glm::mat4 get_model_matrix();

    virtual glm::vec3 get_border(glm::vec3 direction) = 0;

    void set_position(var<glm::vec3> position);
    void set_rotation(var<glm::vec3> rotation);
    void set_scale(var<glm::vec3> scale);
protected:
    var<glm::vec3> position;
    var<glm::vec3> rotation;
    var<glm::vec3> scale;
    var<glm::vec3> offset;

    glm::mat4 model;
    
    void update_model_matrix();
};