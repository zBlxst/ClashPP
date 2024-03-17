#include "Buildings/Building.hpp"

#include "Village.hpp"
#include "GameManager.hpp"
#include "Buttons/BuildingButtons/BuildingButton.hpp"
#include "Buttons/BuildingButtons/UpgradeButton.hpp"
#include "Buttons/BuildingButtons/InfoButton.hpp"


#include <iostream>
#include <chrono>

Building::Building(Village &village, GameManager &game_manager, sf::Texture &texture) : Clickable(game_manager.get_window_manager(), texture, true, true), m_id(Building::max_id++),
	m_game_manager(game_manager), m_village(village), m_level(0), m_level_max(0), m_size_in_blocks(0), m_position_in_village_i(0), m_position_in_village_j(0), 
	m_moving(false), m_selected(false), m_upgrading(false) {
	
	add_button(std::make_shared<InfoButton>(*this, game_manager));
	add_button(std::make_shared<UpgradeButton>(*this, game_manager));

	update_stats();
}

void Building::display() {
	if (!m_moving) {
		Displayable::display();
	} else {
		display_ghost();
	}

	if (m_selected and m_visible) {
		int pos_x = m_position_x - m_window_manager.get_camera().get_x() + (m_ghost_position_in_village_i - m_position_in_village_i)*m_game_manager.get_window_manager().get_width_block();
		int pos_y = m_position_y - m_window_manager.get_camera().get_y() + (m_ghost_position_in_village_j - m_position_in_village_j)*m_game_manager.get_window_manager().get_height_block();
	
		sf::RectangleShape rectangle;
		rectangle.setPosition(sf::Vector2f(pos_x, pos_y));
		rectangle.setSize(sf::Vector2f(get_width(), get_height()));
		if (m_moving) {
			if (can_lock()) {
				rectangle.setFillColor(sf::Color(0, 255, 0, 100));
			} else {
				rectangle.setFillColor(sf::Color(255, 0, 0, 100));
			}
		} else {
			rectangle.setFillColor(sf::Color(255, 255, 255, 100));
		}
		m_window_manager.get_window().draw(rectangle);
	}
}

void Building::display_ghost() {
	int pos_x = m_position_x - m_window_manager.get_camera().get_x() + (m_ghost_position_in_village_i - m_position_in_village_i)*m_game_manager.get_window_manager().get_width_block();
	int pos_y = m_position_y - m_window_manager.get_camera().get_y() + (m_ghost_position_in_village_j - m_position_in_village_j)*m_game_manager.get_window_manager().get_height_block();
	m_sprite.setPosition(pos_x, pos_y);
	m_window_manager.get_window().draw(m_sprite);

}

int Building::get_id() {
	return m_id;
}

int Building::get_class_id() {
	return m_class_id;
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

float Building::get_gold_cost(int level) {
	return 0;
}

float Building::get_mana_cost(int level) {
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

void Building::on_select() {
	m_selected = true;
	for (size_t i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->load(i, m_buttons.size());
	}
}
void Building::on_unselect() {
	m_selected = false;
	for (size_t i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->unload();
	}
}

bool Building::can_upgrade() {
	return 	m_village.can_afford(get_gold_cost(), get_mana_cost()) and
			m_level < m_level_max and
			!m_upgrading;
}

void Building::start_upgrade() {
	if (!can_upgrade()) {
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

void Building::add_button(std::shared_ptr<BuildingButton> button) {
	m_buttons.push_back(button);
	m_game_manager.get_window_manager().get_village_scene()->add_button(button);
}

void Building::on_click() {
	if (m_village.get_village_scene()->get_selected_building_id() == m_id) {
		interact();
	} else {
		m_village.get_village_scene()->select_building(*this);
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

void Building::set_ghost_position_in_village(int i, int j) {
	m_ghost_position_in_village_i = i;
	m_ghost_position_in_village_j = j;
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

bool Building::can_lock() {
	return !m_village.ghost_intersect(*this) and m_ghost_position_in_village_i >= 0 and m_ghost_position_in_village_i + m_size_in_blocks < Village::SIZE_IN_BLOCKS and m_ghost_position_in_village_j >= 0 and m_ghost_position_in_village_j + m_size_in_blocks < Village::SIZE_IN_BLOCKS;
}

void Building::lock_position() {
	if (can_lock()) {
		m_position_in_village_i = m_ghost_position_in_village_i;
		m_position_in_village_j = m_ghost_position_in_village_j;
		move(m_position_in_village_i * m_game_manager.get_window_manager().get_width_block(), m_position_in_village_j * m_game_manager.get_window_manager().get_height_block());
	} else {
		m_ghost_position_in_village_i = m_position_in_village_i;
		m_ghost_position_in_village_j = m_position_in_village_j;
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

void Building::start_moving() {
	m_moving = true;
}
void Building::stop_moving() {
	m_moving = false;
}