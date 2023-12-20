#pragma once

#include "../../common.hpp"
#include "../../components/component.hpp"
#include "../../util/geometry.hpp"

class interactable {
public:
    interactable(glm::vec2 position, std::unique_ptr<component> obj);

    glm::vec2 get_position() const;

    /* check if point is within the bounds of obj */
    bool hit(glm::vec2 point);
protected:
    glm::vec2 position;

    std::unique_ptr<component> obj;
};