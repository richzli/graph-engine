#include "data.hpp"

data::data(int value) {
    this->value = value;
}

data::data() : data(0) {}

template<typename T>
T data::get(std::string key) {
    if (typeid(T) != typeid(int)) {
        return T();
    }

    if (key != "value") {
        return 0;
    }

    return this->value;
}

template<typename T>
bool data::set(std::string key, T value) {
    if (typeid(T) == typeid(int) && key == "value") {
        this->value = value;
        return true;
    }

    return false;
}

std::string data::label() {
    return std::to_string(this->value);
}

data_object::data_object(std::shared_ptr<data> value) {
    this->value = value;
}

data_object::data_object() : data_object(std::make_shared<data>()) { }

template<typename T>
T data_object::get(std::string key) {
    return this->value->get<T>(key);
}

template<typename T>
bool data_object::set(std::string key, T value) {
    return this->value->set<T>(key, value);
}