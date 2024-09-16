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

std::vector<glm::vec3> node_component::get_vertices() {
    return vertices;
}

glm::mat4 node_component::get_model_matrix() {
    update_model_matrix();
    return model;
}

void node_component::apply(std::shared_ptr<node_component> animation) {
    this->component::apply(animation);

    for (int chan : animation->position.get_channels()) {
        if (animation->position[chan]->active) {
            this->position[chan] = animation->position[chan]->copy();
        }
    }

    for (int chan : animation->rotation.get_channels()) {
        if (animation->rotation[chan]->active) {
            this->rotation[chan] = animation->rotation[chan]->copy();
        }
    }

    for (int chan : animation->scale.get_channels()) {
        if (animation->scale[chan]->active) {
            this->scale[chan] = animation->scale[chan]->copy();
        }
    }

    for (int chan : animation->offset.get_channels()) {
        if (animation->offset[chan]->active) {
            this->offset[chan] = animation->offset[chan]->copy();
        }
    }
}

void node_component::update_model_matrix() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, position());
    model *= glm::eulerAngleXYZ(rotation().x, rotation().y, rotation().z);
    model = glm::scale(model, scale());
}