#include "arrow.hpp"

arrow::arrow(
    glm::vec3 src,
    glm::vec3 dst,
    float width,
    glm::vec4 color
) : line(src, dst, width, color) { 
    init_buffers();
}

arrow::arrow(
    glm::vec2 src,
    glm::vec2 dst,
    float width
) : arrow(glm::vec3(src, 0.0f), glm::vec3(dst, 0.0f), width, BLACK) { }

arrow::arrow(const arrow & a) : line(a) {
    init_buffers();
}

std::shared_ptr<component> arrow::copy() {
    return std::make_shared<arrow>(*this);
}

void arrow::calc_vertices() {
    float dist = glm::length(dst() - src());
    glm::vec3 v = glm::normalize(dst() - src());
    if (dist == 0) v = ZERO3;
    glm::vec3 perp(v.y, -v.x, 0.0f);

    glm::vec3 end = dst() - v * (2 * width());
    glm::vec3 bgn;
    if (dist <= 2 * width()) {
        bgn = end;
    } else {
        bgn = src();
    }

    vertices = {
        bgn + perp * (width() / 2),
        bgn - perp * (width() / 2),
        end - perp * (width() / 2),
        end - perp * width(),
        dst(),
        end + perp * width(),
        end + perp * (width() / 2),
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