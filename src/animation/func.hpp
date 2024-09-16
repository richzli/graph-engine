#pragma once

#include "../common.hpp"
#include "anim.hpp"

template <typename T>
class func : public anim<T> {
public:
    func(std::function<T(double)> f);

    std::shared_ptr<anim<T>> copy() override;

    T at(double t) override;
protected:
    std::function<T(double)> f;
};

#include "func.tpp"