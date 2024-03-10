#pragma once

#include <SFML/Graphics.hpp>

class AssetsManager {

private:
	sf::Font m_gold_and_mana_font;

	sf::Texture m_gold_mine_1_texture;
	sf::Texture m_gold_tank_1_texture;
	sf::Texture m_mana_mill_1_texture;
	sf::Texture m_mana_tank_1_texture;
	sf::Texture m_town_hall_1_texture;

	sf::Texture m_building_upgrade_texture;
	sf::Texture m_building_info_texture;
	sf::Texture m_collect_gold_texture;
	sf::Texture m_collect_mana_texture;

	sf::Texture m_close_scene_texture;

public:
	AssetsManager();

	sf::Font& get_gold_and_mana_font();
	sf::Texture& get_gold_mine_texture();
	sf::Texture& get_gold_tank_texture();
	sf::Texture& get_mana_mill_texture();
	sf::Texture& get_mana_tank_texture();
	sf::Texture& get_town_hall_texture();

	sf::Texture& get_building_upgrade_texture();
	sf::Texture& get_building_info_texture();
	sf::Texture& get_collect_gold_texture();
	sf::Texture& get_collect_mana_texture();
	sf::Texture& get_close_scene_texture();


};