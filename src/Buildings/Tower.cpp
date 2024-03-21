#include "Buildings/Tower.hpp"

#include "GameManager.hpp"
#include "Troops/Troop.hpp"

Tower::Tower(Village &village, GameManager &game_manager) : Building(village, game_manager, game_manager.get_window_manager().get_assets_manager().get_tower_texture()), 
																m_cost(0) {
	m_class_id = Building::TOWER_ID;
	m_size_in_blocks = Tower::SIZE;
	m_level = 0;
	m_level_max = Tower::MAX_LEVEL;
}



float Tower::get_gold_cost() {
	return m_cost;
}

float Tower::get_gold_cost(int level) {
	return COSTS[level];
}


std::string Tower::get_class_name() {
	return "Tower";
}

void Tower::update_stats() {
	Building::update_stats();
	m_cost = Tower::COSTS[m_level];
	m_upgrade_time = Tower::UPGRADE_TIMES[m_level];
	m_max_hp = Tower::MAX_HPS[m_level];
	m_attack = Tower::ATTACKS[m_level];
	m_range = Tower::RANGES[m_level];
}

std::shared_ptr<Troop> Tower::get_troop_component(std::shared_ptr<Army> army, std::shared_ptr<Army> opponents) {
	m_troop_component = std::make_shared<Troop>(m_game_manager, m_texture, army, opponents, m_max_hp, m_attack, 2000, m_range, 0, false, m_size_in_blocks);
	m_troop_component->move(get_x(), get_y());


	return m_troop_component;

}