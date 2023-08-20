#include "scene.hpp"

scene::scene() {
    origin = { 0, 0 };
    scale = { _config.width, _config.height };

    _shader = std::make_shared<shader>("basic", "basic");
}

void scene::add_component(std::shared_ptr<component> obj) {
    objects.push_back(obj);
}

void scene::draw() {
    _shader->use();

    glm::mat4 projection = glm::ortho(origin.x, origin.x + scale.x, origin.y, origin.y + scale.y, -1.0f, 1.0f);
    _shader->set_mat4("projection", projection);

    for (std::shared_ptr<component> obj : objects) {
        obj->draw(_shader);
    }
}