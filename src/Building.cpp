#include "Building.hpp"

#include "Village.hpp"
#include "GameManager.hpp"

#include <iostream>

Building::Building(Village &village, GameManager &game_manager, sf::Texture &texture) : Clickable(game_manager.get_window_manager(), texture), m_id(Building::max_id++),
	m_game_manager(game_manager), m_village(village), m_level(0), m_level_max(0), m_size_in_blocks(0), m_position_in_village_i(0), m_position_in_village_j(0) {
	update_stats();
}


int Building::get_id() {
	return m_id;
}

float Building::get_gold_tank_capacity() {
	return 0;
}

float Building::get_mana_tank_capacity() {
	return 0;
}

float Building::get_gold_cost() {
	return 0;
}

float Building::get_mana_cost() {
	return 0;
}

int Building::get_level() {
	return m_level;
}

void Building::level_up() {
	if (m_level < m_level_max) {
		m_level += 1;
	}
	update_stats();
	m_village.update();
}

void Building::update_stats() {}

void Building::interact() {}

void Building::start_upgrade() {
	if (m_level >= m_level_max) {
		return;
	}
	if (m_village.get_resources_manager().get_gold() < get_gold_cost()) {
		return;
	}
	if (m_village.get_resources_manager().get_mana() < get_mana_cost()) {
		return;
	}
	m_village.get_resources_manager().add_gold(-get_gold_cost());
	m_village.get_resources_manager().add_mana(-get_mana_cost());
	level_up();
}

void Building::print_infos() {
	std::cout << get_class_name() << std::endl;
	std::cout << "\tLevel : " << m_level << "/" << m_level_max << " // " ;
	std::cout << "Gold cost : " << (long)get_gold_cost() << " // " << "Mana cost : " << (long)get_mana_cost() << std::endl;
}

void Building::update_sprite() {
	m_size_x = m_size_in_blocks*m_game_manager.get_window_manager().get_width_block();
	m_size_y = m_size_in_blocks*m_game_manager.get_window_manager().get_height_block();
	Displayable::update_sprite();
}

void Building::on_click() {
	interact();
}

bool Building::intersect(Building &other) {
	return 	m_position_in_village_i < other.get_position_in_village_i() + other.get_size() and 
			m_position_in_village_i + m_size_in_blocks > other.get_position_in_village_i() and
			m_position_in_village_j < other.get_position_in_village_j() + other.get_size() and 
			m_position_in_village_j + m_size_in_blocks > other.get_position_in_village_j();
}

bool Building::ghost_intersect(Building &other) {
	return 	m_ghost_position_in_village_i < other.get_position_in_village_i() + other.get_size() and 
			m_ghost_position_in_village_i + m_size_in_blocks > other.get_position_in_village_i() and
			m_ghost_position_in_village_j < other.get_position_in_village_j() + other.get_size() and 
			m_ghost_position_in_village_j + m_size_in_blocks > other.get_position_in_village_j();
}

GameManager& Building::get_game_manager() {
	return m_game_manager;
}

int Building::get_position_in_village_i() {
	return m_position_in_village_i;
}

int Building::get_position_in_village_j() {
	return m_position_in_village_j;
}

void Building::lock_position() {
	if (!m_village.ghost_intersect(*this) and m_ghost_position_in_village_i >= 0 and m_ghost_position_in_village_i + m_size_in_blocks < Village::SIZE_IN_BLOCKS and m_ghost_position_in_village_j >= 0 and m_ghost_position_in_village_j + m_size_in_blocks < Village::SIZE_IN_BLOCKS) {
		m_position_in_village_i = m_ghost_position_in_village_i;
		m_position_in_village_j = m_ghost_position_in_village_j;
		move(m_position_in_village_i * m_game_manager.get_window_manager().get_width_block(), m_position_in_village_j * m_game_manager.get_window_manager().get_height_block());
	} else {
		std::cout << "Can't lock position !" << std::endl;
	}
}

int Building::get_size() {
	return m_size_in_blocks;
}

bool Building::is_position_relative() {
	return true;
}