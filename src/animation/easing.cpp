#include "easing.hpp"

std::function<double(double)> easing::linear() {
    return [](double t) { return t; };
}

double easing::clamp(double x, double lo, double hi) {
    const double t = x < lo ? lo : x;
    return t > hi ? hi : t;
}