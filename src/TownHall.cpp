#include "TownHall.hpp"
#include "GameManager.hpp"

TownHall::TownHall(Village &village, GameManager &game_manager) : Building(village, game_manager, game_manager.get_window_manager().get_assets_manager().get_town_hall_texture()), 
																m_cost(0) {
	m_size_in_blocks = TownHall::SIZE;
	m_level = 1;
	m_level_max = TownHall::MAX_LEVEL;
	village.set_town_hall(std::make_shared<TownHall>(*this));
}



float TownHall::get_gold_cost() {
	return m_cost;
}

std::string TownHall::get_class_name() {
	return "TownHall";
}

void TownHall::update_stats() {
	Building::update_stats();
	m_cost = TownHall::COSTS[m_level];
}