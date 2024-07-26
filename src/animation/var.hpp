#pragma once

#include "../common.hpp"
#include "anim.hpp"

template <class T>
class var {
public:
    var(T val) : var(std::make_shared<anim<T>>(val), {}) { }
    var(std::shared_ptr<anim<T>> ani);
    var(std::shared_ptr<anim<T>> ani, std::chrono::time_point<std::chrono::steady_clock> start);

    operator T();
    virtual T operator()(double t);
    T operator()(std::chrono::time_point<std::chrono::steady_clock> time);
    T operator()();

    void set_anim(std::shared_ptr<anim<T>> ani, std::chrono::time_point<std::chrono::steady_clock> start);
    void set_anim(std::shared_ptr<anim<T>> ani);
private:
    std::shared_ptr<anim<T>> ani;
    std::chrono::time_point<std::chrono::steady_clock> start;
};

#include "var.tpp"