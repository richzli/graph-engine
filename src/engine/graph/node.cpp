#include "node.hpp"

node::node(
    glm::vec2 position,
    std::unique_ptr<component> obj
) : interactable(position, std::move(obj)) { }