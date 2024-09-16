#include "node.hpp"
#include "edge.hpp"

edge::edge(
    int id,
    std::shared_ptr<node> u,
    std::shared_ptr<node> v,
    bool directed,
    std::shared_ptr<data> value
) : item(value), id(id), u(u), v(v), directed(directed) {
    if (this->directed) {
        this->component = std::static_pointer_cast<edge_component>(
            _component_defaults._edge_directed->copy()
        );
    } else {
        this->component = std::static_pointer_cast<edge_component>(
            _component_defaults._edge_undirected->copy()
        );
    }

    // this updates the component, as well
    this->set_u(u);
    this->set_v(v);
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

    this->component->src[BASE] =  std::make_shared<func<glm::vec3>>(
        [u = this->u](double t) -> glm::vec3 {
            std::shared_ptr<node> src = u.lock();
            if (src != nullptr) {
                return std::static_pointer_cast<node_component>(src->get_component())->position();
            }
            return ZERO3;
        }
    );
}

void edge::set_v(std::shared_ptr<node> v) {
    this->v = v;
    
    if (!directed) {
        this->component->dst[BASE] = std::make_shared<func<glm::vec3>>(
            [v = this->v](double _) -> glm::vec3 {
                std::shared_ptr<node> dst = v.lock();
                if (dst != nullptr) {
                    return std::static_pointer_cast<node_component>(dst->get_component())->position();
                }
                return ZERO3;
            }
        );
    } else {
        this->component->dst[BASE] = std::make_shared<func<glm::vec3>>(
            [u = this->u, v = this->v](double _) -> glm::vec3 {
                std::shared_ptr<node> src = u.lock();
                std::shared_ptr<node> dst = v.lock();
                if (src != nullptr && dst != nullptr) {
                    std::shared_ptr<node_component> s = std::static_pointer_cast<node_component>(src->get_component());
                    std::shared_ptr<node_component> t = std::static_pointer_cast<node_component>(dst->get_component());
                    
                    return t->get_border(s->position() - t->position());
                }
                return ZERO3;
            }
        );
    }
}

void edge::update_endpoints() {
    this->component->src = std::static_pointer_cast<node_component>(this->get_u()->get_component())->position();
    this->component->dst = std::static_pointer_cast<node_component>(this->get_v()->get_component())->position();
}