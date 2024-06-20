#include "node.hpp"
#include "edge.hpp"

node::node(
    int index,
    std::shared_ptr<data> value
) : data_object(value) {
    this->index = index;

    this->component = std::static_pointer_cast<node_component>(
        _component_defaults._node->copy()
    );
}

node::node() : node(0, std::make_shared<data>()) { }

node::~node() {

}

std::shared_ptr<node_component> node::get_component() const {
    return this->component;
}

int node::get_index() const {
    return this->index;
}

void node::set_component(std::shared_ptr<node_component> component) {
    this->component = component;
}

edge & node::operator[](int i) {
    return *(this->edges[i]);
}

bool node::add_edge(std::shared_ptr<edge> e) {
    if (e->get_u()->get_index() == this->index) {
        this->edges[e->get_v()->get_index()] = e;
        return true;
    }

    if (e->get_v()->get_index() == this->index) {
        this->edges[e->get_u()->get_index()] = e;
        return true;
    }

    return false;
}

bool node::remove_edge(std::shared_ptr<edge> e) {
    int u = e->get_u()->get_index(), v = e->get_v()->get_index();
    if (u == this->index && this->edges[v] == e) {
        this->edges.erase(v);
        return true;
    }

    if (v == this->index && this->edges[u] == e) {
        this->edges.erase(u);
        return true;
    }

    return false;
}