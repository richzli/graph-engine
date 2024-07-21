#include "graph.hpp"

graph::graph(int n, bool directed) {
    this->node_cnt = n;
    for (int i = 0; i < n; ++i) {
        nodes[i] = std::make_shared<node>();
    }

    this->edge_cnt = 0;

    this->directed = directed;
}

graph::graph(int n) : graph(n, false) { }

graph::graph() : graph(0) { }

std::map<int, std::shared_ptr<node>> & graph::get_nodes() {
    return this->nodes;
}

std::map<int, std::shared_ptr<edge>> & graph::get_edges() {
    return this->edges;
}

node & graph::operator[](int i) {
    return *(this->nodes[i]);
}

int graph::add_edge(int u, int v) {
    std::shared_ptr<edge> e = std::make_shared<edge>(this->edge_cnt, this->nodes[u], this->nodes[v], this->directed);

    if ((*this)[u].add_edge(e) && (*this)[v].add_edge(e)) {
        this->edges[this->edge_cnt] = e;
        return this->edge_cnt++;
    } else {
        (*this)[u].remove_edge(e);
        (*this)[v].remove_edge(e);
        return -1;
    }
}

int graph::add_node() {
    this->nodes[node_cnt] = std::make_shared<node>();
    return node_cnt++;
}