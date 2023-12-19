#include "ManaMill.hpp"
#include "Village.hpp"
#include "GameManager.hpp"

#include <string>
#include <iostream>
#include <chrono>

ManaMill::ManaMill(Village &village, GameManager &game_manager) : ResourceGenerator(village, game_manager, game_manager.get_window_manager().get_assets_manager().get_mana_mill_texture()) {
	m_production_thread = std::make_shared<std::thread>(ManaMill::production_thread_function, std::ref(*this));
	m_game_manager.add_thread(m_production_thread);
}

float ManaMill::get_mana_production() {
	return m_production;
}

float ManaMill::get_mana_capacity() {
	return m_capacity;
}

float ManaMill::get_gold_cost() {
	return m_cost;
}

void ManaMill::update_stats() {
	ResourceGenerator::update_stats();
}

void ManaMill::print_infos() {
	ResourceGenerator::print_infos();
	std::cout << "\tMana production : " << (long)get_mana_production() << std::endl;
}


std::string ManaMill::get_class_name() {
	return "ManaMill";
}

void ManaMill::production_thread_function(ManaMill &obj) {
	while (obj.m_game_manager.is_running()) {
		obj.add_stored(obj.get_production() / 3600 * ResourceGenerator::DEBUG_MULTIPLIER);
		// std::cout << "Stored : " << (long)obj.get_stored() << "/" << (long)obj.get_capacity() << std::endl;  
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void ManaMill::interact() {
	float overflow = m_stored + m_village.get_resources_manager().get_mana() - m_village.get_resources_manager().get_mana_max() ;
	m_village.get_resources_manager().add_mana(m_stored);
	m_stored = std::max(overflow, 0.0f);
}