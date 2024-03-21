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
	m_width(width), m_height(height), m_width_block(width/50), m_height_block(height/50),
	m_window(sf::RenderWindow(sf::VideoMode(width, height), "ClashPP")), m_camera(Camera(0, 0)) {}

void WindowManager::start() {
	std::cout << "Starting WM" << std::endl;
}

void WindowManager::stop() {
	m_window.close();
}

void WindowManager::display() {
	m_window.clear();
	m_game_manager.get_current_scene()->render();
	m_window.display();
}


int WindowManager::get_width_block() {
	return m_width_block;
}

int WindowManager::get_height_block() {
	return m_height_block;
}

int WindowManager::get_width() {
	return m_width;
}

int WindowManager::get_height() {
	return m_height;
}

sf::RenderWindow& WindowManager::get_window() {
	return m_window;
}

AssetsManager& WindowManager::get_assets_manager() {
	return m_assets_manager;
}

GameManager& WindowManager::get_game_manager() {
	return m_game_manager;
}

void WindowManager::manage_events() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_game_manager.stop();
		} else {
			m_game_manager.get_current_scene()->recv_event(event);
		}
	}
}

Camera& WindowManager::get_camera() {
	return m_camera;
}