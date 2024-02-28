#include "Buildings/Building.hpp"

#include "Village.hpp"
#include "GameManager.hpp"

#include <iostream>
#include <chrono>

Building::Building(Village &village, GameManager &game_manager, sf::Texture &texture) : Clickable(game_manager.get_window_manager(), texture), m_id(Building::max_id++),
	m_game_manager(game_manager), m_village(village), m_level(0), m_level_max(0), m_size_in_blocks(0), m_position_in_village_i(0), m_position_in_village_j(0), m_upgrading(false) {
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
	m_upgrading = false;
	if (m_level < m_level_max) {
		m_level += 1;
	}
	update_stats();
	m_village.update();
	m_sprite.setColor(sf::Color(255, 255, 255));
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
	if (m_upgrading) {
		return;
	}

	m_upgrading = true;
	m_upgrade_step = 0;
	m_village.get_resources_manager().add_gold(-get_gold_cost());
	m_village.get_resources_manager().add_mana(-get_mana_cost());
	m_sprite.setColor(sf::Color(100, 100, 100));
	m_upgrading_thread = std::make_shared<std::thread>(Building::upgrade_thread_function, std::ref(*this));
	m_game_manager.add_thread(m_upgrading_thread);
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
	if (m_village.get_village_scene().get_selected_building_id() == m_id) {
		interact();
	} else {
		m_village.get_village_scene().selected_building(m_id);
	}
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

void Building::upgrade_thread_function(Building &obj) {
	while (obj.m_upgrade_step < obj.m_upgrade_time and obj.m_game_manager.is_running()) {
		obj.m_upgrade_step += 1 * Building::DEBUG_MULTIPLIER_TIME;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Upgrade : " << obj.m_upgrade_step << "/" << obj.m_upgrade_time << std::endl;
	}
	obj.level_up();
}