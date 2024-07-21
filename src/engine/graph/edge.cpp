#include "node.hpp"
#include "edge.hpp"

edge::edge(
    int id,
    std::shared_ptr<node> u,
    std::shared_ptr<node> v,
    bool directed,
    std::shared_ptr<data> value
) : item(value) {
    this->u = u;
    this->v = v;
    this->directed = directed;

    if (this->directed) {
        this->component = std::static_pointer_cast<edge_component>(
            _component_defaults._edge_directed->copy()
        );
    } else {
        this->component = std::static_pointer_cast<edge_component>(
            _component_defaults._edge_undirected->copy()
        );
    }
}

edge::edge(
    int id,
    std::shared_ptr<node> u,
    std::shared_ptr<node> v,
    bool directed
) : edge(id, u, v, directed, std::make_shared<data>()) { }

edge::edge(
    int id,
    std::shared_ptr<node> u,
    std::shared_ptr<node> v
) : edge(id, u, v, false) { }

edge::~edge() {

}

std::shared_ptr<component> edge::get_component() const {
    return this->component;
}

int edge::get_id() const {
    return this->id;
}

std::shared_ptr<node> edge::get_u() const {
    return u.lock();
}

std::shared_ptr<node> edge::get_v() const {
    return v.lock();
}

void edge::set_u(std::shared_ptr<node> u) {
    this->u = u;
}

void edge::set_v(std::shared_ptr<node> v) {
    this->v = v;
}

void edge::update_endpoints() {
    this->component->set_src(std::static_pointer_cast<node_component>(this->get_u()->get_component())->get_position());
    this->component->set_dst(std::static_pointer_cast<node_component>(this->get_v()->get_component())->get_position());
}