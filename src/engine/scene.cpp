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
    glm::mat4 projection = glm::ortho(origin.x, origin.x + scale.x, origin.y, origin.y + scale.y, -1.0f, 1.0f);

    for (std::shared_ptr<component> obj : objects) {
        obj->draw(projection);
    }
}