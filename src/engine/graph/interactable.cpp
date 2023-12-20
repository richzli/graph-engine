#include "interactable.hpp"

interactable::interactable(glm::vec2 position, std::unique_ptr<component> obj) {
    this->position = position;
    this->obj = std::move(obj);
}

glm::vec2 interactable::get_position() const {
    return position;
}

bool interactable::hit(glm::vec2 point) {
    glm::vec2 point_adj(
        glm::inverse(obj->get_model_matrix()) * glm::vec4(point, 0.0f, 1.0f)
    );

    std::vector<glm::vec2> vertices = obj->get_vertices();
    int size = vertices.size();
    int rays = 0;
    for (int i = 0; i < size; ++i) {
        rays += left_of_segment(vertices[i], vertices[(i+1) % size], point_adj);
    }

    return rays % 2 == 0;
}