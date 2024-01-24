#pragma once

#include "../components/core.hpp"
#include "render/shader.hpp"

class scene {
public:
    scene();

    glm::vec2 get_origin() const;

    void set_origin(glm::vec2 origin);
    void set_size(glm::vec2 size);

    void add_component(std::shared_ptr<component> obj);

    void select(glm::vec2 pt);
    void deselect();
    void drag(glm::vec2 d);

    void draw();
private:
    glm::vec2 origin;
    glm::vec2 size;

    glm::vec2 convert_pt(glm::vec2 pt);
    glm::vec2 convert_d(glm::vec2 d);

    std::vector<std::shared_ptr<component>> objects;
    std::shared_ptr<component> selected_object;
};