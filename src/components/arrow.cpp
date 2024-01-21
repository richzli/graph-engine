#include "arrow.hpp"

arrow::arrow(
    glm::vec2 src,
    glm::vec2 dst,
    float width,
    glm::vec3 color
) : line(src, dst, width, color) { 
    init_buffers();
}

arrow::arrow(
    glm::vec2 src,
    glm::vec2 dst,
    float width
) : arrow(src, dst, width, BLACK) { }

void arrow::calc_vertices() {
    float dist = glm::length(dst - src);
    glm::vec2 v = glm::normalize(dst - src);
    if (dist == 0) v = ZERO2;
    glm::vec2 perp(v.y, -v.x);

    glm::vec2 end = dst - glm::normalize(dst - src) * (2 * width);
    glm::vec2 bgn;
    if (dist <= 2 * width) {
        bgn = end;
    } else {
        bgn = src;
    }

    vertices = {
        bgn + perp * (width/2),
        bgn - perp * (width/2),
        end - perp * (width/2),
        end - perp * width,
        dst,
        end + perp * width,
        end + perp * (width/2),
    };
}

void arrow::calc_indices() {
    indices = {
        0, 1, 2,
        2, 6, 0,
        2, 3, 4,
        2, 4, 6,
        4, 5, 6,
    };
}