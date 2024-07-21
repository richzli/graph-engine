#include "data.hpp"

data::data(int value) {
    this->value = value;
}

data::data() : data(0) {}

template<typename T>
T data::get(std::string key) const {
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

std::string data::label() const {
    return std::to_string(this->value);
}