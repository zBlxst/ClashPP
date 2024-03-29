#include "Buildings/ResourceGenerator.hpp"

#include <chrono>
#include <thread>
#include <memory>

#include "GameManager.hpp"

ResourceGenerator::ResourceGenerator(Village &village, GameManager &game_manager, sf::Texture &texture) : Building(village, game_manager, texture), 
				m_production(0), m_stored(0), m_capacity(0) {
	m_size_in_blocks = ResourceGenerator::SIZE;
	m_level_max = ResourceGenerator::MAX_LEVEL;

	m_production_thread = std::make_shared<std::thread>(ResourceGenerator::production_thread_function, std::ref(*this));
	m_game_manager.add_thread(m_production_thread);
}

void ResourceGenerator::update_stats() {
	Building::update_stats();
	m_production = ResourceGenerator::PRODUCTIONS[m_level];
	m_capacity = ResourceGenerator::CAPACITIES[m_level];
	m_cost = ResourceGenerator::COSTS[m_level];
	m_upgrade_time = ResourceGenerator::UPGRADE_TIMES[m_level];
	m_max_hp = ResourceGenerator::MAX_HPS[m_level];
}

void ResourceGenerator::print_infos() {
	Building::print_infos();
}

float ResourceGenerator::get_stored() {
	return m_stored;
}

void ResourceGenerator::add_stored(float amount) {
	m_stored = std::max(0.0f, std::min(m_stored + amount, m_capacity));
}

float ResourceGenerator::get_production() {
	return m_production;
}

float ResourceGenerator::get_capacity() {
	return m_capacity;
}

void ResourceGenerator::production_thread_function(ResourceGenerator &obj) {
	while (obj.m_game_manager.is_running()) {
		if (obj.m_upgrading) {
			std::cout << "Waiting for upgrade" << std::endl;
			obj.m_upgrading_thread->join();
			std::cout << "Upgrade is over" << std::endl;
		}
		obj.add_stored(obj.get_production() / 3600 * ResourceGenerator::DEBUG_MULTIPLIER);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

std::string ResourceGenerator::get_save_string() {
	return get_class_name() + " " + 
		   std::to_string(m_level) + " " + 
		   std::to_string((int)m_upgrade_step) + " " + 
		   std::to_string(m_ghost_position_in_village_i) + " " + 
		   std::to_string(m_ghost_position_in_village_j) + " " +
		   std::to_string(m_stored);
}

void ResourceGenerator::restore_state(std::string state) {
	sscanf(state.c_str(), "%d %le %d %d %f", &m_level, &m_upgrade_step, &m_position_in_village_i, &m_position_in_village_j, &m_stored);
	if (m_upgrade_step > 0) {
		start_upgrade(true);
	}

	update_stats();
}