#pragma once

#include "../common.hpp"

/* sign function */
int sgn(float x);
/* cross product of 2d vectors u and v */
float cross(glm::vec2 u, glm::vec2 v);
/* checks if c lies on segment ab */
bool on_segment(glm::vec2 a, glm::vec2 b, glm::vec2 c);
/* 
 * checks if segments ab and cd intersect
 * returns 0 if no intersection, 1 if intersect at one point, and 2 if intersect at infinitely many
 */
int segment_intersect(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d);
/* checks if c is to the left of segment ab */
int left_of_segment(glm::vec2 a, glm::vec2 b, glm::vec2 c);