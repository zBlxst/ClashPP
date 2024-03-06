#include "Buildings/GoldTank.hpp"

#include <string>
#include <iostream>

#include "GameManager.hpp"


GoldTank::GoldTank(Village &village, GameManager &game_manager) : Tank(village, game_manager, game_manager.get_window_manager().get_assets_manager().get_gold_tank_texture()) {
	m_class_id = Building::GOLDTANK_ID;
}

float GoldTank::get_gold_tank_capacity() {
	return m_capacity;
}

float GoldTank::get_mana_cost() {
	return m_cost;
}

void GoldTank::print_infos() {
	Tank::print_infos();
	std::cout << "\tGold capacity : " << m_capacity << std::endl;
}


std::string GoldTank::get_class_name() {
	return "GoldTank";
}