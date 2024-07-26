#pragma once

#include "../common.hpp"

class easing {
public:
    static std::function<double(double)> linear();

    static double clamp(double x, double lo, double hi);
};