#include "component.hpp"

component::component(glm::vec4 color) : color(color) {
    this->create_buffers();
}

component::component() : component(BLACK) { }

component::component(const component & c) : color(c.color), vertices(c.vertices), indices(c.indices) {
    this->create_buffers();
}

component::~component() {
    this->delete_buffers();
}

void component::apply(std::shared_ptr<component> animation) {
    for (int chan : animation->color.get_channels()) {
        if (animation->color[chan]->active) {
            this->color[chan] = animation->color[chan]->copy();
        }
    }
}

void component::draw(const glm::mat4 & view, const glm::mat4 & projection) {
    this->get_shader()->use();

    this->bind_uniforms();
    this->get_shader()->set_mat4("view", view);
    this->get_shader()->set_mat4("projection", projection);

    this->update_vertices();
    this->update_indices();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void component::create_buffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /*
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) 0);

    glBindVertexArray(0);
    */
}

void component::init_buffers() {
    glBindVertexArray(VAO);

    this->calc_vertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);

    this->calc_indices();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *) 0);

    glBindVertexArray(0);
}

void component::delete_buffers() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void component::update_vertices() {
    this->calc_vertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), &vertices.front());
}

void component::update_indices() {
    this->calc_indices();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), &indices.front());
}