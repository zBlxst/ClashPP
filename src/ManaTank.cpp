#include "ManaTank.hpp"

#include <string>
#include <iostream>

#include "GameManager.hpp"

ManaTank::ManaTank(Village &village, GameManager &game_manager) : Tank(village, game_manager, game_manager.get_window_manager().get_assets_manager().get_mana_tank_texture()) {}

float ManaTank::get_mana_tank_capacity() {
	return m_capacity;
}

float ManaTank::get_gold_cost() {
	return m_cost;
}

void ManaTank::print_infos() {
	Tank::print_infos();
	std::cout << "\tMana capacity : " << m_capacity << std::endl;
}


std::string ManaTank::get_class_name() {
	return "ManaTank";
}