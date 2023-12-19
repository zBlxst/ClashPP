#include "ResourceGenerator.hpp"

ResourceGenerator::ResourceGenerator(Village &village, GameManager &game_manager, sf::Texture &texture) : Building(village, game_manager, texture), 
				m_production(0), m_stored(0), m_capacity(0) {
	m_size_in_blocks = ResourceGenerator::SIZE;
	m_level_max = ResourceGenerator::MAX_LEVEL;
}

void ResourceGenerator::update_stats() {
	Building::update_stats();
	m_production = ResourceGenerator::PRODUCTIONS[m_level];
	m_capacity = ResourceGenerator::CAPACITIES[m_level];
	m_cost = ResourceGenerator::COSTS[m_level];
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
