#include "GoldMine.hpp"
#include "Village.hpp"
#include "GameManager.hpp"

#include <string>
#include <iostream>
#include <chrono>

GoldMine::GoldMine(Village &village, GameManager &game_manager) : ResourceGenerator(village, game_manager, game_manager.get_window_manager().get_assets_manager().get_gold_mine_texture()) {
	m_production_thread = std::make_shared<std::thread>(GoldMine::production_thread_function, std::ref(*this));
	m_game_manager.add_thread(m_production_thread);
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

void GoldMine::production_thread_function(GoldMine &obj) {
	while (obj.m_game_manager.is_running()) {
		obj.add_stored(obj.get_production() / 3600 * ResourceGenerator::DEBUG_MULTIPLIER);
		// std::cout << "Stored : " << (long)obj.get_stored() << "/" << (long)obj.get_capacity() << std::endl;  
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void GoldMine::interact() {
	float overflow = m_stored + m_village.get_resources_manager().get_gold() - m_village.get_resources_manager().get_gold_max() ;
	m_village.get_resources_manager().add_gold(m_stored);
	m_stored = std::max(overflow, 0.0f);
}