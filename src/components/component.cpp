#include "component.hpp"

component::component(
    glm::vec3 position,
    glm::vec3 rotation,
    glm::vec3 scale,
    glm::vec3 color
) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->color = color;

    create_buffers();
}

component::component() : component(ZERO3, ZERO3, ONE3, BLACK) { }

component::~component() {
    delete_buffers();
}

glm::vec3 component::get_position() const {
    return position;
}

glm::vec3 component::get_rotation() const {
    return rotation;
}

glm::vec3 component::get_scale() const {
    return scale;
}

glm::vec3 component::get_color() const {
    return color;
}

std::vector<glm::vec2> component::get_vertices() const {
    return vertices;
}

glm::mat4 component::get_model_matrix() const {
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    model *= glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
    model = glm::scale(model, scale);
    return model;
}

void component::set_position(glm::vec3 position) {
    this->position = position;
}

void component::set_rotation(glm::vec3 rotation) {
    this->rotation = rotation;
}

void component::set_scale(glm::vec3 scale) {
    this->scale = scale;
}

void component::set_color(glm::vec3 color) {
    this->color = color;
}

void component::draw(std::shared_ptr<shader> _shader) {
    _shader->use();

    _shader->set_mat4("model", get_model_matrix());
    _shader->set_vec3("color", color);

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

void component::delete_buffers() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void component::update_vertices() {
    calc_vertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec2), &vertices.front());
}