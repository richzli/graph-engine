#include "geometry.hpp"

int sgn(float x) {
    return (x > 0) - (x < 0);
}

float dot(glm::vec2 u, glm::vec2 v) {
    glm::vec2 w = u * v;
    return w.x + w.y;
}

float cross(glm::vec2 u, glm::vec2 v) {
    return (glm::cross(glm::vec3(u, 0.0f), glm::vec3(v, 0.0f))).z;
}

bool on_segment(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
    return cross(a-c, b-c) == 0 && dot(a-c, b-c) <= 0;
}

int segment_intersect(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d) {
    float oa = cross(d-c, a-c), ob = cross(d-c, b-c),
        oc = cross(b-a, c-a), od = cross(b-a, d-a);
    
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
        return 1;
    }

    return std::min(2, 0 + on_segment(a, b, c) + on_segment(a, b, d) +
        on_segment(c, d, a) + on_segment(c, d, b));
}

int left_of_segment(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
    glm::vec2 d(c.x, std::max(a.y, b.y));
    return segment_intersect(a, b, c, d);
}