#pragma once

#include "../common.hpp"
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
    void zoom(bool in);

    void draw();
private:
    glm::vec2 origin;
    glm::vec2 size;
    float distance;

    glm::vec2 pt_to_world(glm::vec2 pt);
    glm::vec2 v_to_world(glm::vec2 v);

    glm::vec2 pt_to_screen(glm::vec2 pt);
    glm::vec2 v_to_screen(glm::vec2 v);

    std::shared_ptr<graph> g;
    std::shared_ptr<item> selected_object;

    void update_edges();

    void draw_text(std::string label, std::string text, glm::vec2 pos, int size);
};