#include "anim.hpp"

template <typename T>
anim<T>::anim(T val) : value(val) { };

template <typename T>
T anim<T>::get(double time) {
    return this->value;
}
