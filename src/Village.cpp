#include "Village.hpp"
#include <iostream>

#include "Buildings/Building.hpp"
#include "Buildings/TownHall.hpp"
#include "GameManager.hpp"

Village::Village(GameManager &game_manager) : 	m_game_manager(game_manager),
												m_buildings(std::vector<std::shared_ptr<Building>>()), 
					 							m_resources_manager(*this) {}

void Village::add_building(std::shared_ptr<Building> b) {
	m_buildings.push_back(b);
	update();	
}

void Village::update() {
	for (size_t i = 0; i < m_buildings.size(); i++) {
		m_buildings[i]->update_stats();
	}
	m_resources_manager.update_max_resources();
}


std::vector<std::shared_ptr<Building>>& Village::get_buildings() {
	return m_buildings;
}

ResourcesManager& Village::get_resources_manager() {
	return m_resources_manager;
}

int Village::get_town_hall_level() {
	return m_town_hall->get_level();
}

void Village::set_town_hall(std::shared_ptr<TownHall> th) {
	m_town_hall = th;
}

bool Village::ghost_intersect(Building &ghost) {
	for (size_t i = 0; i < m_buildings.size(); i++) {
		if (ghost.get_id() != m_buildings[i]->get_id() and ghost.ghost_intersect(*m_buildings[i])) {
			return true;
		}
	}
	return false;
}

void Village::find_free_room(Building &building) {
	for (int i = 0; i < Village::SIZE_IN_BLOCKS - building.get_size(); i++) {
		for (int j = 0; j < Village::SIZE_IN_BLOCKS - building.get_size(); j++) {
			building.m_ghost_position_in_village_i = j;
			building.m_ghost_position_in_village_j = i;
			if (!ghost_intersect(building)) {
				return;
			}
		}
	}
}