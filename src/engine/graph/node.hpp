#pragma once

#include "../../common.hpp"
#include "../../components/node_component.hpp"
#include "item.hpp"

class edge;

class node : public item {
public:
    node();
    node(int id);
    node(int id, std::shared_ptr<data> value);
    ~node();

    std::shared_ptr<component> get_component() const override;
    int get_id() const override;

    void set_component(std::shared_ptr<node_component> component);

    edge & operator[](int i);
    bool add_edge(std::shared_ptr<edge> e);
    bool remove_edge(std::shared_ptr<edge> e);
protected:
    int id;

    std::map<int, std::shared_ptr<edge>> edges;
    std::shared_ptr<node_component> component;
};