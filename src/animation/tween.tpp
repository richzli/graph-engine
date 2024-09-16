#include "tween.hpp"

template <typename T>
tween<T>::tween(std::function<T(double)> path, std::function<double(double)> easing_fn, double duration) : anim<T>(path(0)), path(path), easing_fn(easing_fn), duration(duration) {
    if (this->duration <= 0.0f) {
        this->duration = 1e-10; // small positive value
    }
}

template <typename T>
std::shared_ptr<anim<T>> tween<T>::copy() {
    return std::make_shared<tween<T>>(this->path, this->easing_fn, this->duration);
}

template <typename T>
T tween<T>::at(double t) {
    return path(easing_fn(std::min(t, this->duration) / this->duration));
}