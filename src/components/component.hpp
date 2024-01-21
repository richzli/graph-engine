#pragma once

#include "../common.hpp"
#include "../engine/render/shader.hpp"

class component {
public:
    component();
    ~component();

    void draw(glm::mat4 projection);
protected:
    unsigned int VAO, VBO, EBO;
    /* vertices in counter-clockwise order */
    std::vector<glm::vec2> vertices;
    std::vector<unsigned int> indices;

    void create_buffers();
    void init_buffers();
    void delete_buffers();
    virtual void calc_vertices() = 0;
    virtual void calc_indices() = 0;
    void update_vertices();
    void update_indices();

    virtual std::shared_ptr<shader> get_shader() = 0;
    virtual void bind_uniforms() = 0;
};