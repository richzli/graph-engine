#include "func.hpp"

template <typename T>
func<T>::func(std::function<T(double)> f) : anim<T>(f(0)), f(f) { }

template <typename T>
std::shared_ptr<anim<T>> func<T>::copy() {
    return std::make_shared<func<T>>(this->f);
}

template <typename T>
T func<T>::at(double t) {
    return this->f(t);
}