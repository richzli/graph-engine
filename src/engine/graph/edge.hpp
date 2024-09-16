#pragma once

#include "../../common.hpp"
#include "../../animation/func.hpp"
#include "../../components/edge_component.hpp"
#include "item.hpp"

class node;

class edge : public item {
public:
    edge(int id, std::shared_ptr<node> u, std::shared_ptr<node> v);
    edge(int id, std::shared_ptr<node> u, std::shared_ptr<node> v, bool directed);
    edge(int id, std::shared_ptr<node> u, std::shared_ptr<node> v, bool directed, std::shared_ptr<data> value);
    ~edge();

    std::shared_ptr<component> get_component() const override;
    int get_id() const override;
    std::shared_ptr<node> get_u() const;
    std::shared_ptr<node> get_v() const;

    void set_u(std::shared_ptr<node> u);
    void set_v(std::shared_ptr<node> v);

    void update_endpoints();
protected:
    int id;

    std::weak_ptr<node> u, v;
    bool directed;
    std::shared_ptr<edge_component> component;
};