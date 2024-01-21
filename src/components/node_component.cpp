#include "node_component.hpp"

node_component::node_component(
    glm::vec3 position,
    glm::vec3 rotation,
    glm::vec3 scale,
    glm::vec3 color
) : component() {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->color = color;
}

node_component::node_component() : node_component(ZERO3, ZERO3, ONE3, BLACK) { }

glm::vec3 node_component::get_position() const {
    return position;
}

glm::vec3 node_component::get_rotation() const {
    return rotation;
}

glm::vec3 node_component::get_scale() const {
    return scale;
}

glm::vec3 node_component::get_color() const {
    return color;
}

std::vector<glm::vec2> node_component::get_vertices() const {
    return vertices;
}

glm::mat4 node_component::get_model_matrix() const {
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    model *= glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
    model = glm::scale(model, scale);
    return model;
}

void node_component::set_position(glm::vec3 position) {
    this->position = position;
}

void node_component::set_rotation(glm::vec3 rotation) {
    this->rotation = rotation;
}

void node_component::set_scale(glm::vec3 scale) {
    this->scale = scale;
}

void node_component::set_color(glm::vec3 color) {
    this->color = color;
}