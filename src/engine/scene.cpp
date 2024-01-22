#include "scene.hpp"

scene::scene() {
    origin = { 0, 0 };
    scale = { _config.width, _config.height };
}

void scene::set_origin(glm::vec2 origin) {
    this->origin = origin;
}

void scene::set_scale(glm::vec2 scale) {
    this->scale = scale;
}

void scene::add_component(std::shared_ptr<component> obj) {
    objects.push_back(obj);
}

void scene::draw() {
    glm::mat4 view = glm::lookAt(glm::vec3(origin, 0.0f), glm::vec3(origin, -1.0f), UP);
    glm::mat4 projection = glm::ortho(0.0f, scale.x, 0.0f, scale.y, -1.0f, 1.0f);

    for (std::shared_ptr<component> obj : objects) {
        obj->draw(view, projection);
    }
}