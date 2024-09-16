#pragma once

#include "../common.hpp"
#include "../settings.hpp"
#include "../engine/render/shader.hpp"
#include "../animation/var.hpp"

class component {
public:
    component(glm::vec4 color);
    component();
    component(const component & c);
    ~component();

    virtual std::shared_ptr<component> copy() = 0;

    virtual glm::vec3 get_center() = 0;

    virtual bool hit(glm::vec2 pt) = 0;
    virtual void drag(glm::vec2 d) = 0;

    void apply(std::shared_ptr<component> animation);
    void draw(const glm::mat4 & view, const glm::mat4 & projection);

    var<glm::vec4> color;
protected:
    unsigned int VAO, VBO, EBO;
    /* vertices in counter-clockwise order */
    std::vector<glm::vec3> vertices;
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