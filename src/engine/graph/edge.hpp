#pragma once

#include "../../common.hpp"
#include "../../components/edge_component.hpp"
#include "data.hpp"

class node;

class edge : data_object {
public:
    edge(std::shared_ptr<node> u, std::shared_ptr<node> v);
    edge(std::shared_ptr<node> u, std::shared_ptr<node> v, bool directed);
    edge(std::shared_ptr<node> u, std::shared_ptr<node> v, bool directed, std::shared_ptr<data> value);
    ~edge();

    std::shared_ptr<edge_component> get_component();
    std::shared_ptr<node> get_u() const;
    std::shared_ptr<node> get_v() const;

    void set_u(std::shared_ptr<node> u);
    void set_v(std::shared_ptr<node> v);

    void update_endpoints();
protected:
    std::weak_ptr<node> u, v;
    bool directed;
    std::shared_ptr<edge_component> component;
};