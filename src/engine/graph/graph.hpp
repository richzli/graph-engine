#pragma once

#include "node.hpp"
#include "edge.hpp"

class graph {
public:
    graph();
    graph(int n);
    graph(int n, bool directed);

    const std::map<int, std::shared_ptr<node>> & get_nodes() const;
    const std::set<std::shared_ptr<edge>> & get_edges() const;

    node & operator[](int i);
    bool add_edge(int u, int v);
    int add_node();
private:
    bool directed;
    int next_index;

    std::map<int, std::shared_ptr<node>> nodes;
    std::set<std::shared_ptr<edge>> edges;
};