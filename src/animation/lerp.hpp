#pragma once

#include "../common.hpp"
#include "anim.hpp"

template <typename T>
class lerp : public anim<T> {
public:
    lerp(T val, std::function<T(double)> target, double speed);

    T get(double t) override;
protected:
    double speed;
    double last_eval;
    std::function<T(double)> target;
};

#include "lerp.tpp"