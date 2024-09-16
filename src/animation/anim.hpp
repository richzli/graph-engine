#pragma once

#include "../common.hpp"

template <typename T>
class anim {
public:
    anim(T val);
    anim(T val, time_pt start);

    virtual std::shared_ptr<anim<T>> copy();

    time_pt get_start() const;
    void set_start(time_pt start);

    virtual T at(double t);
    T at(time_pt time);

    bool active;
protected:
    T value;
    time_pt start;
};

#include "anim.tpp"