#include "WindowManager.hpp"

#include <iostream>

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
	m_window(sf::RenderWindow(sf::VideoMode(width, height), "This Is The Title !")) {}

void WindowManager::start() {

	std::cout << "Starting WM" << std::endl; 
	
	m_text_gold.setFont(m_assets_manager.get_gold_and_mana_font());
	m_text_gold.setFillColor(sf::Color::White);
	m_text_gold.setCharacterSize(24);
	m_text_gold.setString("Gold : " + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_gold()));

	m_text_mana.setFont(m_assets_manager.get_gold_and_mana_font());
	m_text_mana.setFillColor(sf::Color::White);
	m_text_mana.setCharacterSize(24);
	m_text_mana.setString("Mana : " + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_mana()));
	m_text_mana.move(0.0, m_text_gold.getLocalBounds().height*(3.0/2.0));

}

void WindowManager::stop() {
	m_window.close();
}

void WindowManager::display() {
	m_text_gold.setString("Gold : " + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_gold()) + "/" + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_gold_max()));
	m_text_mana.setString("Mana : " + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_mana()) + "/" + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_mana_max()));

	m_window.clear();
	for (size_t i = 0; i < m_displayables.size(); i++) {
		m_displayables[i]->display();
	}

	m_window.draw(m_text_gold);
	m_window.draw(m_text_mana);
	m_window.display();
}

void WindowManager::add_displayable(std::shared_ptr<Displayable> displayable) {
	m_displayables.push_back(displayable);
}

void WindowManager::add_clickable(std::shared_ptr<Clickable> clickable) {
	m_clickables.push_back(clickable);
}

void WindowManager::update_sprites() {
	for (size_t i = 0; i < m_displayables.size(); i++) {
		m_displayables[i]->update_sprite();
	}
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

void WindowManager::manage_events() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_game_manager.stop();
		} else if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				case sf::Keyboard::A: 
					if (!event.key.control) {
						m_game_manager.get_village().get_buildings()[0]->start_upgrade();
						m_game_manager.get_village().get_buildings()[0]->print_infos();	
					} else {
						m_game_manager.create_building<TownHall>();
					}
					break;
				case sf::Keyboard::B:
					if (!event.key.control) {
						m_game_manager.get_village().get_buildings()[1]->start_upgrade();
						m_game_manager.get_village().get_buildings()[1]->print_infos();	
					} else {
						m_game_manager.create_building<GoldTank>();
					}
					break;
				case sf::Keyboard::C:
					if (!event.key.control) {
						m_game_manager.get_village().get_buildings()[2]->start_upgrade();
						m_game_manager.get_village().get_buildings()[2]->print_infos();	
					} else {
						m_game_manager.create_building<GoldMine>();
					}
					break;
				case sf::Keyboard::D:
					if (!event.key.control) {
						m_game_manager.get_village().get_buildings()[3]->start_upgrade();
						m_game_manager.get_village().get_buildings()[3]->print_infos();	
					} else {
						m_game_manager.create_building<ManaMill>();
					}
					break;
				case sf::Keyboard::E:
					if (!event.key.control) {
						m_game_manager.get_village().get_buildings()[4]->start_upgrade();
						m_game_manager.get_village().get_buildings()[4]->print_infos();	
					} else {
						m_game_manager.create_building<ManaTank>();
					}
					break;
				case sf::Keyboard::R:
					m_game_manager.get_village().get_resources_manager().add_gold(10000000000000000);
					m_game_manager.get_village().get_resources_manager().add_mana(10000000000000000);
					break;
				default:
					break;	
			}

		} else if (event.type == sf::Event::MouseButtonPressed) {
			switch (event.mouseButton.button) {
				case sf::Mouse::Left:
					for (size_t i = 0; i < m_clickables.size(); i++) {
						if (m_clickables[i]->is_clicked(event.mouseButton.x, event.mouseButton.y)) {
							m_clickables[i]->on_click();
							break;
						}
					}
					break;
				default:
					break;

			}
		}
	}
}