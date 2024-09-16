#pragma once

#include "../common.hpp"
#include "anim.hpp"

template <typename T>
class lerp : public anim<T> {
public:
    lerp(T val, std::function<T(double)> target, double speed);

    std::shared_ptr<anim<T>> copy() override;

    T at(double t) override;
protected:
    double speed;
    double last_eval;
    std::function<T(double)> target;
};

#include "lerp.tpp"