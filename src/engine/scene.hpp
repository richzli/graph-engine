#pragma once

#include "../components/core.hpp"
#include "graph/graph.hpp"
#include "render/shader.hpp"

class scene {
public:
    scene();
    scene(std::shared_ptr<graph> g);

    const std::shared_ptr<graph> get_graph() const;
    glm::vec2 get_origin() const;

    void set_origin(glm::vec2 origin);
    void set_size(glm::vec2 size);

    void select(glm::vec2 pt);
    void deselect();
    void drag(glm::vec2 d);

    void draw();
private:
    glm::vec2 origin;
    glm::vec2 size;

    glm::vec2 convert_pt(glm::vec2 pt);
    glm::vec2 convert_d(glm::vec2 d);

    std::shared_ptr<graph> g;
    std::shared_ptr<component> selected_object;

    void update_edges();
};