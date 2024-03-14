#include "Buildings/GoldMine.hpp"

#include "Village.hpp"
#include "GameManager.hpp"

#include <string>
#include <iostream>
#include <chrono>

#include "Buttons/BuildingButtons/CollectGoldButton.hpp"

GoldMine::GoldMine(Village &village, GameManager &game_manager) : 
		ResourceGenerator(village, game_manager, game_manager.get_window_manager().get_assets_manager().get_gold_mine_texture()) {

	m_class_id = Building::GOLDMINE_ID;
	add_button(std::make_shared<CollectGoldButton>(*this, game_manager));
}

float GoldMine::get_gold_production() {
	return m_production;
}

float GoldMine::get_gold_capacity() {
	return m_capacity;
}

float GoldMine::get_mana_cost() {
	return m_cost;
}

float GoldMine::get_mana_cost(int level) {
	return COSTS[level];
}


void GoldMine::update_stats() {
	ResourceGenerator::update_stats();
}

void GoldMine::print_infos() {
	ResourceGenerator::print_infos();
	std::cout << "\tGold production : " << (long)get_gold_production() << std::endl;
}


std::string GoldMine::get_class_name() {
	return "GoldMine";
}


void GoldMine::collect() {
	float overflow = m_stored + m_village.get_resources_manager().get_gold() - m_village.get_resources_manager().get_gold_max() ;
	m_village.get_resources_manager().add_gold(m_stored);
	m_stored = std::max(overflow, 0.0f);
}

void GoldMine::interact() {

}