#pragma once

#include "../common.hpp"
#include "../animation/core.hpp"
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

    void move(glm::vec2 d);
    void zoom(bool in);

    void hover(glm::vec2 pt);
    void unhover();
    void select(glm::vec2 pt);
    void deselect();
    void drag(glm::vec2 d);

    void draw();
private:
    glm::vec2 origin;
    glm::vec2 size;
    float distance;

    glm::vec2 screen_to_world_pt(glm::vec2 pt);
    glm::vec2 screen_to_world_v(glm::vec2 v);

    glm::vec2 world_to_screen_pt(glm::vec2 pt);
    glm::vec2 world_to_screen_v(glm::vec2 v);

    std::shared_ptr<graph> g;
    std::shared_ptr<item> hovered_object;
    std::shared_ptr<item> selected_object;

    void update_edges();

    void draw_text(std::string label, std::string text, glm::vec2 pos, int size);
};