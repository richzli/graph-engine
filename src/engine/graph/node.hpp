#pragma once

#include "../../common.hpp"

#include "interactable.hpp"

class edge;

class node : public interactable {
public:
    node(glm::vec2 position, std::unique_ptr<component> obj);

    void add_in_edge(std::shared_ptr<edge> _edge);
    void add_out_edge(std::shared_ptr<edge> _edge);
protected:
    std::set<std::shared_ptr<edge>> incut, outcut;
};