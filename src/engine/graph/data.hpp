#pragma once

#include "../../common.hpp"

class data {
public:
    data();
    data(int value);

    template<typename T> T get(std::string key) const;
    template<typename T> bool set(std::string key, T value);

    std::string label() const;
protected:
    int value;
};