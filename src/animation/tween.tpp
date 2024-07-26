#include "tween.hpp"

template <typename T>
tween<T>::tween(std::function<T(double)> path, std::function<double(double)> easing_fn, double duration) : anim<T>(path(0)), path(path), easing_fn(easing_fn), duration(duration) {
    if (this->_duration <= 0.0f) {
        this->_duration = 1e-10; // small positive value
    }
}

template <typename T>
T tween<T>::get(double t) {
    return path(easing_fn(t / this->_duration));
}