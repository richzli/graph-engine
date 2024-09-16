#include "anim.hpp"

template <typename T>
anim<T>::anim(T val) : anim(val, std::chrono::steady_clock::now()) { }

template <typename T>
anim<T>::anim(T val, time_pt start) : active(false), value(val), start(start) { }

template <typename T>
std::shared_ptr<anim<T>> anim<T>::copy() {
    return std::make_shared<anim<T>>(this->value, this->start);
}

template <typename T>
time_pt anim<T>::get_start() const {
    return this->start;
}

template <typename T>
void anim<T>::set_start(time_pt start) {
    this->start = start;
}

template <typename T>
T anim<T>::at(double time) {
    return this->value;
}

template <typename T>
T anim<T>::at(time_pt time) {
    return this->at(std::chrono::duration<double>(time - this->start).count());
}