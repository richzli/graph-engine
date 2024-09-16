#include "var.hpp"

template <class T>
var<T>::var(T val) : var(std::make_shared<anim<T>>(val)) { }

template <class T>
var<T>::var(std::shared_ptr<anim<T>> ani) : anis({}) {
    this->set_anim(ani);
}

template<typename T>
var<T> & var<T>::operator=(const T & val) {
    this->anis[BASE] = std::make_shared<anim<T>>(val);
    return *this;
}

template <typename T>
var<T>::operator T() {
    return this->operator()();
}

template <typename T>
T var<T>::operator()(double time) {
    return this->anis[BASE]->at(time);
}

template <typename T>
T var<T>::operator()() {
    return this->anis[BASE]->at(std::chrono::steady_clock::now());
}

template <typename T>
std::shared_ptr<anim<T>> & var<T>::operator[](int i) {
    return this->anis[i];
}

template <typename T>
bool var<T>::has(int i) {
    return this->anis.count(i) != 0;
}

template <typename T>
std::vector<int> var<T>::get_channels() {
    std::vector<int> channels;
    for (auto & [i, _] : anis) {
        channels.push_back(i);
    }
    return channels;
}

template <typename T>
void var<T>::set_anim(std::shared_ptr<anim<T>> ani) {
    this->anis.clear();
    this->anis[BASE] = ani;
}