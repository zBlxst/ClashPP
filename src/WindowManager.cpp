#include "WindowManager.hpp"

#include <iostream>
#include <functional>

#include "GameManager.hpp"
#include "Displayable.hpp"
#include "Clickable.hpp"

#include "Buildings/Building.hpp"
#include "Buildings/GoldTank.hpp"
#include "Buildings/GoldMine.hpp"
#include "Buildings/ManaMill.hpp"
#include "Buildings/ManaTank.hpp"
#include "Buildings/TownHall.hpp"

WindowManager::WindowManager(int width, int height, GameManager &game_manager) : m_game_manager(game_manager), m_assets_manager(),
	m_village_scene(VillageScene(*this, game_manager, true)), m_current_scene(std::ref(m_village_scene)),
	m_width(width), m_height(height), m_width_block(width/50), m_height_block(height/50),
	m_window(sf::RenderWindow(sf::VideoMode(width, height), "This Is The Title !")) {}

void WindowManager::start() {
	std::cout << "Starting WM" << std::endl; 
	m_current_scene.load();
}

void WindowManager::stop() {
	m_current_scene.unload();
	m_window.close();
}

void WindowManager::display() {
	m_current_scene.display();
}


int WindowManager::get_width_block() {
	return m_width_block;
}

int WindowManager::get_height_block() {
	return m_height_block;
}

sf::RenderWindow& WindowManager::get_window() {
	return m_window;
}

AssetsManager& WindowManager::get_assets_manager() {
	return m_assets_manager;
}

Scene& WindowManager::get_current_scene() {
	return m_current_scene;
}

void WindowManager::manage_events() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_game_manager.stop();
		} else {
			m_current_scene.manage_event(event);
		}
	}
}