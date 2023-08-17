#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

struct config {
    int width = 1600;
    int height = 900;
};

extern config _config;