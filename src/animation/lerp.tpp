#include "lerp.hpp"

template <typename T>
lerp<T>::lerp(T val, std::function<T(double)> target, double speed) : anim<T>(val), target(target), speed(speed), last_eval(0) { }

template <typename T>
std::shared_ptr<anim<T>> lerp<T>::copy() {
    return std::make_shared<lerp<T>>(this->value, this->target, this->speed);
}

template <typename T>
T lerp<T>::at(double t) {
    if (t > this->last_eval){
        this->val = this->_target + (this->_target - this->val) * exp(-max(this->_speed, 0.0d) * (t - this->last_eval));
        this->last_eval = t;
    }

    return this->val;
}