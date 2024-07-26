#include "var.hpp"

template <class T>
var<T>::var(std::shared_ptr<anim<T>> ani) : var(ani, std::chrono::steady_clock::now()) { }

template <class T>
var<T>::var(std::shared_ptr<anim<T>> ani, std::chrono::time_point<std::chrono::steady_clock> start) : ani(ani), start(start) { }

template <typename T>
var<T>::operator T() {
    return this->operator()();
}

template <typename T>
T var<T>::operator()(double time) {
    return this->ani->get(time);
}

template <typename T>
T var<T>::operator()(std::chrono::time_point<std::chrono::steady_clock> time) {
    return this->operator()(std::chrono::duration<double>(time - this->start).count());
}

template <typename T>
T var<T>::operator()() {
    return this->operator()(std::chrono::steady_clock::now());
}

template <typename T>
void var<T>::set_anim(std::shared_ptr<anim<T>> ani, std::chrono::time_point<std::chrono::steady_clock> start) {
    this->ani = ani;
    this->start = start;
}

template <typename T>
void var<T>::set_anim(std::shared_ptr<anim<T>> ani) {
    this->set_anim(ani, std::chrono::steady_clock::now());
}