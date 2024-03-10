#include "AssetsManager.hpp"

#include <iostream>

AssetsManager::AssetsManager() {
	std::cout << "Constructor of the AM" << std::endl;
	m_gold_and_mana_font.loadFromFile("assets/font.ttf");

	m_gold_mine_1_texture.loadFromFile("assets/Buildings/Gold_mine_1.png");
	m_gold_tank_1_texture.loadFromFile("assets/Buildings/Gold_tank_1.png");
	m_mana_mill_1_texture.loadFromFile("assets/Buildings/Mana_mill_1.png");
	m_mana_tank_1_texture.loadFromFile("assets/Buildings/Mana_tank_1.png");
	m_town_hall_1_texture.loadFromFile("assets/Buildings/Town_hall_1.png");

	m_building_upgrade_texture.loadFromFile("assets/Buttons/BuildingButtons/Upgrade.png");
	m_building_info_texture.loadFromFile("assets/Buttons/BuildingButtons/Info.png");
	m_collect_gold_texture.loadFromFile("assets/Buttons/BuildingButtons/CollectGold.png");
	m_collect_mana_texture.loadFromFile("assets/Buttons/BuildingButtons/CollectMana.png");
	m_close_scene_texture.loadFromFile("assets/Buttons/CloseScene.png");
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
sf::Texture& AssetsManager::get_building_upgrade_texture() {
	return m_building_upgrade_texture;
}
sf::Texture& AssetsManager::get_building_info_texture() {
	return m_building_info_texture;
}
sf::Texture& AssetsManager::get_collect_gold_texture() {
	return m_collect_gold_texture;
}
sf::Texture& AssetsManager::get_collect_mana_texture() {
	return m_collect_mana_texture;
}
sf::Texture& AssetsManager::get_close_scene_texture() {
	return m_close_scene_texture;
}