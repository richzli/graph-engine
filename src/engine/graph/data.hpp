#pragma once

#include "../../common.hpp"

class data {
public:
    data();
    data(int value);

    template<typename T> T get(std::string key);
    template<typename T> bool set(std::string key, T value);

    std::string label();
protected:
    int value;
};

class data_object {
public:
    data_object();
    data_object(std::shared_ptr<data> value);

    template<typename T> T get(std::string key);
    template<typename T> bool set(std::string key, T value);
protected:
    std::shared_ptr<data> value;
};