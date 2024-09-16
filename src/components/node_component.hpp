#pragma once

#include "component.hpp"

class node_component : public component {
public:
    node_component();
    node_component(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 offset, glm::vec4 color);
    node_component(const node_component & nc);

    std::vector<glm::vec3> get_vertices();
    glm::mat4 get_model_matrix();

    virtual glm::vec3 get_border(glm::vec3 direction) = 0;

    var<glm::vec3> position;
    var<glm::vec3> rotation;
    var<glm::vec3> scale;
    var<glm::vec3> offset;

    void apply(std::shared_ptr<node_component> animation);
protected:
    glm::mat4 model;
    
    void update_model_matrix();
};