#include "node_component.hpp"

node_component::node_component(
    glm::vec3 position,
    glm::vec3 rotation,
    glm::vec3 scale,
    glm::vec3 color
) : component(color) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;

    update_model_matrix();
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

std::vector<glm::vec2> node_component::get_vertices() const {
    return vertices;
}

glm::mat4 node_component::get_model_matrix() const {
    return model;
}

void node_component::set_position(glm::vec3 position) {
    this->position = position;
    update_model_matrix();
}

void node_component::set_rotation(glm::vec3 rotation) {
    this->rotation = rotation;
    update_model_matrix();
}

void node_component::set_scale(glm::vec3 scale) {
    this->scale = scale;
    update_model_matrix();
}

void node_component::update_model_matrix() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model *= glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
    model = glm::scale(model, scale);
}