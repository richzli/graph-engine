#include "node.hpp"
#include "edge.hpp"

node::node(
    int id,
    std::shared_ptr<data> value
) : item(value), id(id) {
    this->component = std::static_pointer_cast<node_component>(
        _component_defaults._node->copy()
    );
}

node::node(
    int id
) : node(id, std::make_shared<data>()) { }

node::node() : node(0, std::make_shared<data>()) { }

node::~node() {

}

std::shared_ptr<component> node::get_component() const {
    return this->component;
}

int node::get_id() const {
    return this->id;
}

void node::set_component(std::shared_ptr<node_component> component) {
    this->component = component;
}

edge & node::operator[](int i) {
    return *(this->edges[i]);
}

bool node::add_edge(std::shared_ptr<edge> e) {
    if (e->get_u()->get_id() == this->id) {
        this->edges[e->get_v()->get_id()] = e;
        return true;
    }

    if (e->get_v()->get_id() == this->id) {
        this->edges[e->get_u()->get_id()] = e;
        return true;
    }

    return false;
}

bool node::remove_edge(std::shared_ptr<edge> e) {
    int u = e->get_u()->get_id(), v = e->get_v()->get_id();
    if (u == this->id && this->edges[v] == e) {
        this->edges.erase(v);
        return true;
    }

    if (v == this->id && this->edges[u] == e) {
        this->edges.erase(u);
        return true;
    }

    return false;
}