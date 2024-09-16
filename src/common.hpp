#pragma once

#include <algorithm>
#include <any>
#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <set>
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
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_stdlib.h"

typedef std::chrono::time_point<std::chrono::steady_clock> time_pt;

#define ZERO2   glm::vec2( 0.0f,  0.0f)
#define ZERO3   glm::vec3( 0.0f,  0.0f,  0.0f)
#define ONE3    glm::vec3( 1.0f,  1.0f,  1.0f)

#define RIGHT   glm::vec3( 1.0f,  0.0f,  0.0f)
#define LEFT    glm::vec3(-1.0f,  0.0f,  1.0f)
#define UP      glm::vec3( 0.0f,  1.0f,  0.0f)
#define DOWN    glm::vec3( 0.0f, -1.0f,  0.0f)
#define FORWARD glm::vec3( 0.0f,  0.0f,  1.0f)
#define BACK    glm::vec3( 0.0f,  0.0f, -1.0f)

#define BLACK   glm::vec4(0.00f, 0.00f, 0.00f, 1.00f)
#define RED     glm::vec4(1.00f, 0.00f, 0.00f, 1.00f)
#define WHITE   glm::vec4(1.00f, 1.00f, 1.00f, 1.00f)

#define BASE    0
#define OVERLAY 1