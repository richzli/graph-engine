#include "edge.hpp"

edge::edge(
    std::shared_ptr<node> src,
    std::shared_ptr<node> dst,
    bool directed
) : interactable(ZERO2, std::unique_ptr<line>(nullptr)) {
    this->src = src;
    this->dst = dst;
    this->directed = directed;

    if (directed) {
        this->obj = std::make_unique<arrow>(
            src->get_position(),
            dst->get_position(),
            10.0f
        );
    } else {
        this->obj = std::make_unique<line>(
            src->get_position(),
            dst->get_position(),
            10.0f
        );
    }
}

edge::edge(
    std::shared_ptr<node> src,
    std::shared_ptr<node> dst
) : edge(src, dst, false) { }

std::shared_ptr<node> edge::get_src() const {
    return src;
}

std::shared_ptr<node> edge::get_dst() const {
    return dst;
}

void edge::set_src(std::shared_ptr<node> src) {
    this->src = src;
    update_src();
}

void edge::set_dst(std::shared_ptr<node> dst) {
    this->dst = dst;
    update_dst();
}

void edge::update_src() {
    this->obj->set_src(src->get_position());
}

void edge::update_dst() {
    this->obj->set_dst(dst->get_position());
}