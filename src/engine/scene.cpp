#include "scene.hpp"

scene::scene(std::shared_ptr<graph> g) : g(g) {
    origin = { 0, 0 };
    size = { _config.width, _config.height };
    distance = 1;

    hovered_object = nullptr;
    selected_object = nullptr;
}

scene::scene() : scene(std::make_shared<graph>(0, true)) { }

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

/*
 * Moves the viewable area.
 * 
 * @param d The move distance in screen coordinates.
 */
void scene::move(glm::vec2 d) {
    this->set_origin(this->get_origin() - screen_to_world_v(d));
}

/*
 * Zooms in or out.
 *
 * @param in `true` if zooming in, `false` if zooming out.
 */
void scene::zoom(bool in) {
    if (in) {
        distance *= _config.zoom_factor;
    } else {
        distance /= _config.zoom_factor;
    }
}

void scene::hover(glm::vec2 pt) {
    if (hovered_object != nullptr) {
        if (!hovered_object->get_component()->hit(screen_to_world_pt(pt))) {
            unhover();
        }
    }

    for (auto & [i, v] : this->g->get_nodes()) {
        std::shared_ptr<component> obj = v->get_component();
        if (obj->hit(screen_to_world_pt(pt))) {
            hovered_object = v;
            return;
        }
    }
    for (auto & [i, e] : this->g->get_edges()) {
        std::shared_ptr<component> obj = e->get_component();
        if (obj->hit(screen_to_world_pt(pt))) {
            hovered_object = e;
            return;
        }
    }
    
    unhover();
}

void scene::unhover() {
    hovered_object = nullptr;
}

void scene::select(glm::vec2 pt) {
    for (auto & [i, v] : this->g->get_nodes()) {
        std::shared_ptr<component> obj = v->get_component();
        if (obj->hit(screen_to_world_pt(pt))) {
            obj->set_color(RED);
            selected_object = v;
            selected_object->select();
            return;
        }
    }
    for (auto & [i, e] : this->g->get_edges()) {
        std::shared_ptr<component> obj = e->get_component();
        if (obj->hit(screen_to_world_pt(pt))) {
            obj->set_color(RED);
            selected_object = e;
            selected_object->select();
            return;
        }
    }
    
    deselect();
}

void scene::deselect() {
    if (selected_object != nullptr) {
        selected_object->get_component()->set_color(BLACK);
        selected_object->deselect();
    }
    selected_object = nullptr;
}

/*
 * Executes a drag event.
 *
 * @param d The drag distance in screen coordinates.
 */
void scene::drag(glm::vec2 d) {
    if (selected_object != nullptr) {
        selected_object->get_component()->drag(screen_to_world_v(d));
    }
}

/*
 * Draws all objects in the scene.
 */
void scene::draw() {
    glm::mat4 view = glm::lookAt(glm::vec3(origin, 0.0f), glm::vec3(origin, -1.0f), UP);
    glm::mat4 projection = glm::ortho(-size.x / 2.0f / distance, size.x / 2.0f / distance, -size.y / 2.0f / distance, size.y / 2.0f / distance, -1.0f, 1.0f);

    update_edges();

    for (const auto & [i, e] : this->g->get_edges()) {
        if (e != selected_object) {
            e->get_component()->draw(view, projection);
            draw_text("edge" + std::to_string(e->get_id()), e->label(), e->get_component()->get_center(), 0);
        }
    }
    if (std::dynamic_pointer_cast<edge>(selected_object) != nullptr) {
        selected_object->get_component()->draw(view, projection);
        draw_text("edge" + std::to_string(selected_object->get_id()), selected_object->label(), selected_object->get_component()->get_center(), 0);
    }

    for (const auto & [i, v] : this->g->get_nodes()) {
        if (v != selected_object) {
            v->get_component()->draw(view, projection);
            draw_text("node" + std::to_string(v->get_id()), v->label(), v->get_component()->get_center(), 0);
        }
    }
    if (std::dynamic_pointer_cast<node>(selected_object) != nullptr) {
        selected_object->get_component()->draw(view, projection);
        draw_text("node" + std::to_string(selected_object->get_id()), selected_object->label(), selected_object->get_component()->get_center(), 0);
    }
}

/*
 * Converts a point from screen coordinates into world-space coordinates.
 *
 * @param pt The point.
 */
glm::vec2 scene::screen_to_world_pt(glm::vec2 pt) {
    return this->get_origin() - glm::vec2(1.0f, -1.0f) * size / 2.0f / distance + screen_to_world_v(pt);
}

/*
 * Converts a vector from screen coordinates into world-space coordinates.
 *
 * @param d The vector.
 */
glm::vec2 scene::screen_to_world_v(glm::vec2 v) {
    return glm::vec2(1.0f, -1.0f) / distance * v;
}

/*
 * Converts a point from world-space coordinates into screen coordinates.
 *
 * @param pt The point.
 */
glm::vec2 scene::world_to_screen_pt(glm::vec2 pt) {
    return world_to_screen_v(pt + glm::vec2(1.0f, -1.0f) * size / 2.0f / distance - this->get_origin());
}

/*
 * Converts a vector from screen coordinates into world-space coordinates.
 *
 * @param d The vector.
 */
glm::vec2 scene::world_to_screen_v(glm::vec2 v) {
    return glm::vec2(1.0f, -1.0f) * distance * v;
}

void scene::update_edges() {
    /* 
    for (const auto & [i, e] : this->g->get_edges()) {
        e->update_endpoints();
    }
    */
}

void scene::draw_text(std::string label, std::string text, glm::vec2 pos, int size) {
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::SetNextWindowPos(world_to_screen_pt(pos) - (glm::vec2) ImGui::CalcTextSize(text.c_str()) / 2.0f);

    ImGui::Begin(label.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs);

    ImGui::PushStyleColor(ImGuiCol_Text, WHITE);
    ImGui::Text(text.c_str());
    ImGui::PopStyleColor();

    ImGui::End();

    ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}