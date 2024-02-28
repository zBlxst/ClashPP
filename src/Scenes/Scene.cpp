#include "Scenes/Scene.hpp"

#include "Displayable.hpp"
#include "Clickable.hpp"

Scene::Scene(WindowManager &window_manager, bool visible) : m_window_manager(window_manager), m_visible(visible) {}

void Scene::add_displayable(std::shared_ptr<Displayable> displayable) {
	m_displayables.push_back(displayable);
}

void Scene::add_clickable(std::shared_ptr<Clickable> clickable) {
	m_clickables.push_back(clickable);
}

void Scene::update_sprites() {
	for (size_t i = 0; i < m_displayables.size(); i++) {
		m_displayables[i]->update_sprite();
	}
}