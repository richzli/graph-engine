#pragma once

#include "common.hpp"

struct config {
    int width = 1600;
    int height = 900;
    float zoom_factor = 1.1f;
};

extern config _config;

class node_component;
class edge_component;

struct component_defaults {
    std::shared_ptr<node_component> _node;
    std::shared_ptr<edge_component> _edge_directed;
    std::shared_ptr<edge_component> _edge_undirected;
};

extern component_defaults _component_defaults;