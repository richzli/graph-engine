#include "follow.hpp"

template <typename T>
follow<T>::follow(std::function<T(double)> f) : anim<T>(f(0)), f(f) { }

template <typename T>
T follow<T>::get(double t) {
    return this->f(t);
}