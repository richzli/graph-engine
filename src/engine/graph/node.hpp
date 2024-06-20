#pragma once

#include "../../common.hpp"
#include "../../components/node_component.hpp"
#include "data.hpp"

class edge;

class node : data_object {
public:
    node();
    node(int index, std::shared_ptr<data> value);
    ~node();

    std::shared_ptr<node_component> get_component() const;
    int get_index() const;

    void set_component(std::shared_ptr<node_component> component);

    edge & operator[](int i);
    bool add_edge(std::shared_ptr<edge> e);
    bool remove_edge(std::shared_ptr<edge> e);
protected:
    int index;

    std::map<int, std::shared_ptr<edge>> edges;
    std::shared_ptr<node_component> component;
};