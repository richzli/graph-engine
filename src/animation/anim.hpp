#pragma once

#include "../common.hpp"

template <typename T>
class anim {
public:
    anim(T val);

    virtual T get(double t);
protected:
    T value;
};

#include "anim.tpp"