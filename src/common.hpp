#pragma once

#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

#define ZERO2   glm::vec2( 0.0f,  0.0f)
#define ZERO3   glm::vec3( 0.0f,  0.0f,  0.0f)
#define ONE3    glm::vec3( 1.0f,  1.0f,  1.0f)

#define RIGHT   glm::vec3( 1.0f,  0.0f,  0.0f)
#define LEFT    glm::vec3(-1.0f,  0.0f,  1.0f)
#define UP      glm::vec3( 0.0f,  1.0f,  0.0f)
#define DOWN    glm::vec3( 0.0f, -1.0f,  0.0f)
#define FORWARD glm::vec3( 0.0f,  0.0f,  1.0f)
#define BACK    glm::vec3( 0.0f,  0.0f, -1.0f)

#define BLACK   glm::vec3(0.00f, 0.00f, 0.00f)
#define WHITE   glm::vec3(1.00f, 1.00f, 1.00f)

struct config {
    int width = 1600;
    int height = 900;
};

extern config _config;