#include "item.hpp"

item::item(std::shared_ptr<data> value) {
    this->value = value;
    this->selected = false;
}

item::item() : item(std::make_shared<data>()) { }

bool item::is_selected() const {
    return this->selected;
}

void item::select() {
    this->selected = true;
}

void item::deselect() {
    this->selected = false;
}

template<typename T>
T item::get(std::string key) const {
    return this->value->get<T>(key);
}

template<typename T>
bool item::set(std::string key, T value) {
    return this->value->set<T>(key, value);
}

std::string item::label() const {
    return this->value->label();
}