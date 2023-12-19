#include "AssetsManager.hpp"

#include <iostream>

AssetsManager::AssetsManager() {
	std::cout << "Constructor of the AM" << std::endl;
	m_gold_and_mana_font.loadFromFile("assets/font.ttf");

	m_gold_mine_1_texture.loadFromFile("assets/Gold_mine_1.png");
	m_gold_tank_1_texture.loadFromFile("assets/Gold_tank_1.png");
	m_mana_mill_1_texture.loadFromFile("assets/Mana_mill_1.png");
	m_mana_tank_1_texture.loadFromFile("assets/Mana_tank_1.png");
	m_town_hall_1_texture.loadFromFile("assets/Town_hall_1.png");
}

sf::Font& AssetsManager::get_gold_and_mana_font() {
	return m_gold_and_mana_font;
}
sf::Texture& AssetsManager::get_gold_mine_texture() {
	return m_gold_mine_1_texture;
}
sf::Texture& AssetsManager::get_gold_tank_texture() {
	return m_gold_tank_1_texture;
}
sf::Texture& AssetsManager::get_mana_mill_texture() {
	return m_mana_mill_1_texture;
}
sf::Texture& AssetsManager::get_mana_tank_texture() {
	return m_mana_tank_1_texture;
}
sf::Texture& AssetsManager::get_town_hall_texture() {
	return m_town_hall_1_texture;
}