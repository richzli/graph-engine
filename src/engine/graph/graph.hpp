#pragma once

#include "item.hpp"
#include "node.hpp"
#include "edge.hpp"

class graph {
public:
    graph();
    graph(int n);
    graph(int n, bool directed);

    std::map<int, std::shared_ptr<node>> & get_nodes();
    std::map<int, std::shared_ptr<edge>> & get_edges();

    node & operator[](int i);
    int add_edge(int u, int v);
    int add_node();
private:
    bool directed;
    int node_cnt, edge_cnt;

    std::map<int, std::shared_ptr<node>> nodes;
    std::map<int, std::shared_ptr<edge>> edges;
};