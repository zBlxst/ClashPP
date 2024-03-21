#pragma once

#include <SFML/Graphics.hpp>

class AssetsManager {

private:
	sf::Font m_gold_and_mana_font;

	sf::Texture m_gold_mine_1_texture;
	sf::Texture m_gold_tank_1_texture;
	sf::Texture m_mana_mill_1_texture;
	sf::Texture m_mana_tank_1_texture;
	sf::Texture m_tower_1_texture;
	sf::Texture m_town_hall_1_texture;

	sf::Texture m_building_upgrade_texture;
	sf::Texture m_building_info_texture;
	sf::Texture m_collect_gold_texture;
	sf::Texture m_collect_mana_texture;

	sf::Texture m_close_scene_texture;

	sf::Texture m_left_arrow_texture;
	sf::Texture m_right_arrow_texture;

	sf::Texture m_guardian_texture;
	sf::Texture m_hunter_texture;

	sf::Texture m_thunder_god_texture;
	sf::Texture m_druid_texture;

public:
	AssetsManager();

	sf::Font& get_gold_and_mana_font();
	sf::Texture& get_gold_mine_texture();
	sf::Texture& get_gold_tank_texture();
	sf::Texture& get_mana_mill_texture();
	sf::Texture& get_mana_tank_texture();
	sf::Texture& get_tower_texture();
	sf::Texture& get_town_hall_texture();

	sf::Texture& get_building_upgrade_texture();
	sf::Texture& get_building_info_texture();
	sf::Texture& get_collect_gold_texture();
	sf::Texture& get_collect_mana_texture();
	sf::Texture& get_close_scene_texture();

	sf::Texture& get_left_arrow_texture();
	sf::Texture& get_right_arrow_texture();

	sf::Texture& get_guardian_texture();
	sf::Texture& get_hunter_texture();

	sf::Texture& get_thunder_god_texture();
	sf::Texture& get_druid_texture();


};