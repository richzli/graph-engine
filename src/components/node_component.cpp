#include "node_component.hpp"

node_component::node_component(
    glm::vec3 position,
    glm::vec3 rotation,
    glm::vec3 scale,
    glm::vec3 offset,
    glm::vec4 color
) : component(color), position(position), rotation(rotation), scale(scale), offset(offset) {
    update_model_matrix();
}

node_component::node_component() : node_component(ZERO3, ZERO3, ONE3, ZERO3, BLACK) { }

node_component::node_component(const node_component & nc) : component(nc), position(nc.position), rotation(nc.rotation), scale(nc.scale), offset(nc.offset), model(nc.model) { }

glm::vec3 node_component::get_position() {
    return position;
}

glm::vec3 node_component::get_rotation() {
    return rotation;
}

glm::vec3 node_component::get_scale() {
    return scale;
}

std::vector<glm::vec3> node_component::get_vertices() {
    return vertices;
}

glm::mat4 node_component::get_model_matrix() {
    update_model_matrix();
    return model;
}

void node_component::set_position(var<glm::vec3> position) {
    this->position = position;
}

void node_component::set_rotation(var<glm::vec3> rotation) {
    this->rotation = rotation;
}

void node_component::set_scale(var<glm::vec3> scale) {
    this->scale = scale;
}

void node_component::update_model_matrix() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, position());
    model *= glm::eulerAngleXYZ(rotation().x, rotation().y, rotation().z);
    model = glm::scale(model, scale());
}