#include "graph.hpp"

graph::graph(int n, bool directed) {
    this->next_index = n;
    for (int i = 0; i < n; ++i) {
        nodes[i] = std::make_shared<node>();
    }

    this->directed = directed;
}

graph::graph(int n) : graph(n, false) { }

graph::graph() : graph(0) { }

const std::map<int, std::shared_ptr<node>> & graph::get_nodes() const {
    return this->nodes;
}

const std::set<std::shared_ptr<edge>> & graph::get_edges() const {
    return this->edges;
}

node & graph::operator[](int i) {
    return *(this->nodes[i]);
}

bool graph::add_edge(int u, int v) {
    std::shared_ptr<edge> e = std::make_shared<edge>(this->nodes[u], this->nodes[v], this->directed);

    if ((*this)[u].add_edge(e) && (*this)[v].add_edge(e)) {
        this->edges.insert(e);
        return true;
    } else {
        (*this)[u].remove_edge(e);
        (*this)[v].remove_edge(e);
        return false;
    }
}

int graph::add_node() {
    this->nodes[next_index] = std::make_shared<node>();
    return next_index++;
}