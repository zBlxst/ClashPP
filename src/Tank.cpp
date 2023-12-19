#include "Tank.hpp"

Tank::Tank(Village &village, GameManager &game_manager, sf::Texture &texture) : Building(village, game_manager, texture), m_cost(0), m_capacity(0) {
	m_size_in_blocks = Tank::SIZE;
	m_level_max = Tank::MAX_LEVEL;
}

void Tank::update_stats() {
	Building::update_stats();
	m_cost = Tank::COSTS[m_level];
	m_capacity = Tank::CAPACITIES[m_level];
}

void Tank::print_infos() {
	Building::print_infos();
}