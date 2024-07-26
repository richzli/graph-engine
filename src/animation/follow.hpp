#pragma once

#include "../common.hpp"
#include "anim.hpp"

template <typename T>
class follow : public anim<T> {
public:
    follow(std::function<T(double)> f);

    T get(double t) override;
protected:
    std::function<T(double)> f;
};

#include "follow.tpp"