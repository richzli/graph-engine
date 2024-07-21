#pragma once

#include "../../common.hpp"
#include "../../components/component.hpp"
#include "data.hpp"

class item {
public:
    item();
    item(std::shared_ptr<data> value);

    bool is_selected() const;
    void select();
    void deselect();

    virtual std::shared_ptr<component> get_component() const = 0;
    virtual int get_id() const = 0;

    template<typename T> T get(std::string key) const;
    template<typename T> bool set(std::string key, T value);
    std::string label() const;
protected:
    bool selected;

    std::shared_ptr<data> value;
};