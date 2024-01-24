#include "scene.hpp"

scene::scene() {
    origin = { 0, 0 };
    size = { _config.width, _config.height };

    selected_object = nullptr;
}

glm::vec2 scene::get_origin() const {
    return origin;
}

void scene::set_origin(glm::vec2 origin) {
    this->origin = origin;
}

void scene::set_size(glm::vec2 size) {
    this->size = size;
}

void scene::add_component(std::shared_ptr<component> obj) {
    objects.push_back(obj);
}

void scene::select(glm::vec2 pt) {
    for (std::shared_ptr<component> obj : objects) {
        if (obj->hit(convert_pt(pt))) {
            obj->set_color(RED);
            selected_object = obj;
            return;
        }
    }
    selected_object = nullptr;
}

void scene::deselect() {
    if (selected_object != nullptr) {
        selected_object->set_color(BLACK);
    }
    selected_object = nullptr;
}

/*
 * Executes a drag event.
 *
 * @param d The drag distance in screen coordinates.
 */
void scene::drag(glm::vec2 d) {
    if (selected_object == nullptr) {
        this->set_origin(this->get_origin() + convert_d(d));
    } else {
        selected_object->drag(convert_d(d));
    }
}

/*
 * Draws all objects in the scene.
 */
void scene::draw() {
    glm::mat4 view = glm::lookAt(glm::vec3(origin, 0.0f), glm::vec3(origin, -1.0f), UP);
    glm::mat4 projection = glm::ortho(0.0f, size.x, 0.0f, size.y, -1.0f, 1.0f);

    for (std::shared_ptr<component> obj : objects) {
        obj->draw(view, projection);
    }
}

/*
 * Converts a point from screen coordinates into world-space coordinates.
 *
 * @param pt The point.
 */
glm::vec2 scene::convert_pt(glm::vec2 pt) {
    return this->get_origin() + glm::vec2(0.0f, size.y) + convert_d(pt);
}

/*
 * Converts a vector from screen coordinates into world-space coordinates.
 *
 * @param d The vector.
 */
glm::vec2 scene::convert_d(glm::vec2 d) {
    return glm::vec2(1.0f, -1.0f) * d;
}