#pragma once

#include "../common.hpp"
#include "anim.hpp"

template <typename T>
class tween : public anim<T> {
public:
    tween(std::function<T(double)> path, std::function<double(double)> easing_fn, double duration);

    std::shared_ptr<anim<T>> copy() override;

    T at(double t) override;
protected:
    std::function<T(double)> path;
    std::function<double(double)> easing_fn;
    double duration;
};

#include "tween.tpp"