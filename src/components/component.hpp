#pragma once

#include "../common.hpp"
#include "../render/shader.hpp"

class component {
public:
    component(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
    ~component();

    glm::vec3 get_position() const;
    glm::vec3 get_rotation() const;
    glm::vec3 get_scale() const;
    glm::vec3 get_color() const;

    void set_position(glm::vec3 position);
    void set_rotation(glm::vec3 rotation);
    void set_scale(glm::vec3 scale);
    void set_color(glm::vec3 color);

    void draw(std::shared_ptr<shader> _shader);
protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 color;

    unsigned int VAO, VBO, EBO;
    std::vector<glm::vec2> vertices;
    std::vector<unsigned int> indices;

    void create_buffers();
    void delete_buffers();
    virtual void init_vertices() = 0;
    virtual void calc_vertices() = 0;
    void update_vertices();
};