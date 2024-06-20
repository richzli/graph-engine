#include "scene.hpp"

scene::scene(std::shared_ptr<graph> g) {
    origin = { - _config.width / 2, - _config.height / 2 };
    size = { _config.width, _config.height };

    selected_object = nullptr;

    this->g = g;
}

scene::scene() : scene(std::make_shared<graph>()) { }

const std::shared_ptr<graph> scene::get_graph() const {
    return this->g;
}

glm::vec2 scene::get_origin() const {
    return this->origin;
}

void scene::set_origin(glm::vec2 origin) {
    this->origin = origin;
}

void scene::set_size(glm::vec2 size) {
    this->size = size;
}

void scene::select(glm::vec2 pt) {
    for (const auto & [i, v] : this->g->get_nodes()) {
        std::shared_ptr<node_component> obj = v->get_component();
        if (obj->hit(convert_pt(pt))) {
            obj->set_color(RED);
            selected_object = obj;
            return;
        }
    }
    for (const std::shared_ptr<edge> & e : this->g->get_edges()) {
        std::shared_ptr<edge_component> obj = e->get_component();
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
        this->set_origin(this->get_origin() - convert_d(d));
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

    update_edges();

    for (const std::shared_ptr<edge> & e : this->g->get_edges()) {
        e->get_component()->draw(view, projection);
    }
    for (const auto & [i, v] : this->g->get_nodes()) {
        v->get_component()->draw(view, projection);
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

void scene::update_edges() {
    for (const std::shared_ptr<edge> & e : this->g->get_edges()) {
        e->update_endpoints();
    }
}