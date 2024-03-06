#include "Scenes/Scene.hpp"

#include "Displayable.hpp"
#include "Clickable.hpp"
#include "Buttons/Button.hpp"

#include <iostream>

Scene::Scene(WindowManager &window_manager, bool visible) : 
		m_id(Scene::max_id++), m_scene_above(nullptr), m_scene_behind(nullptr), m_window_manager(window_manager), m_visible(visible) {}

void Scene::add_displayable(std::shared_ptr<Displayable> displayable) {
	m_displayables.push_back(displayable);
}

void Scene::add_clickable(std::shared_ptr<Clickable> clickable) {
	m_clickables.push_back(clickable);
}

void Scene::add_button(std::shared_ptr<Button> button) {
	add_clickable(button);
	add_displayable(button);
}

void Scene::update_sprites() {
	for (size_t i = 0; i < m_displayables.size(); i++) {
		m_displayables[i]->update_sprite();
	}
}

void Scene::render() {
	display();
	if (!is_on_top()) {
		m_scene_above->render();
	}
}

void Scene::display_background() {}

void Scene::display() {
	for (size_t i = 0; i < m_displayables.size(); i++) {
		m_displayables[i]->update_sprite();
		m_displayables[i]->display();
	}
}

bool Scene::is_on_top() {
	return m_scene_above == nullptr;
}

bool Scene::is_on_bottom() {
	return m_scene_behind == nullptr;
}

int Scene::get_id() {
	return m_id;
}

void Scene::recv_event(sf::Event event) {
	if (is_on_top()) {
		manage_event(event);
	} else {
		m_scene_above->recv_event(event);
	}
}

bool Scene::manage_event(sf::Event event) {
	bool catched = false;
	if (event.type == sf::Event::MouseButtonPressed) {
		switch (event.mouseButton.button) {
			case sf::Mouse::Left:
				for (size_t i = 0; i < m_clickables.size(); i++) {
					if (m_clickables[i]->is_clicked(event.mouseButton.x, event.mouseButton.y)) {
						m_clickables[i]->on_click();
						catched = true;
						break;
					}
				}
				break;
			default:
				break;
		}
	}
	return catched;
}

void Scene::back_on_top() {
	m_scene_above.reset();
}

void Scene::unload() {
	if (!is_on_bottom()) {
		m_scene_behind->back_on_top();
	}
}

void Scene::load() {}

void Scene::load(std::shared_ptr<Scene> behind) {
	load();
	m_scene_behind = behind;
}