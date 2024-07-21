#include "component.hpp"

component::component(glm::vec4 color) {
    this->create_buffers();
    
    this->color = color;
}

component::component() : component(BLACK) { }

component::component(const component & c) {
    this->create_buffers();

    this->color = c.color;
    this->vertices = c.vertices;
    this->indices = c.indices;
}

component::~component() {
    this->delete_buffers();
}

glm::vec4 component::get_color() const {
    return color;
}

void component::set_color(glm::vec4 color) {
    this->color = color;
}

void component::draw(const glm::mat4 & view, const glm::mat4 & projection) {
    this->get_shader()->use();

    this->bind_uniforms();
    this->get_shader()->set_mat4("view", view);
    this->get_shader()->set_mat4("projection", projection);

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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) 0);

    glBindVertexArray(0);
    */
}

void component::init_buffers() {
    glBindVertexArray(VAO);

    this->calc_vertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices.front(), GL_STATIC_DRAW);

    this->calc_indices();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) 0);

    glBindVertexArray(0);
}

void component::delete_buffers() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void component::update_vertices() {
    this->calc_vertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec2), &vertices.front());
}

void component::update_indices() {
    this->calc_indices();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), &indices.front());
}