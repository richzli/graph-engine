#pragma once

#include "../common.hpp"
#include "anim.hpp"

template <class T>
class var {
public:
    var(T val);
    var(std::shared_ptr<anim<T>> ani);

    var & operator=(const T & val);

    operator T();
    T operator()(double t);
    T operator()();

    std::shared_ptr<anim<T>> & operator[](int i);
    bool has(int i);

    std::vector<int> get_channels();

    void set_anim(std::shared_ptr<anim<T>> ani);
private:
    std::map<int, std::shared_ptr<anim<T>>> anis;
};

#include "var.tpp"