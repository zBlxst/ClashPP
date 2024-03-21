#include "Village.hpp"
#include <iostream>

#include "Buildings/Building.hpp"

#include "Buildings/GoldTank.hpp"
#include "Buildings/GoldMine.hpp"
#include "Buildings/ManaMill.hpp"
#include "Buildings/ManaTank.hpp"
#include "Buildings/TownHall.hpp"
#include "Buildings/Tower.hpp"

#include "GameManager.hpp"

Village::Village(GameManager &game_manager) : 	
				m_game_manager(game_manager),
				m_buildings(std::vector<std::shared_ptr<Building>>()), 
				m_resources_manager(*this) {}


void Village::add_building(std::shared_ptr<Building> building) {
	m_buildings.push_back(building);
	m_game_manager.get_village_scene()->add_displayable(building);
	m_game_manager.get_village_scene()->add_clickable(building);
	find_free_room(*building);
	building->lock_position();
	building->update_stats();
	building->update_sprite();
	update();	
}

void Village::update() {
	for (size_t i = 0; i < m_buildings.size(); i++) {
		m_buildings[i]->update_stats();
	}
	m_resources_manager.update_max_resources();
}

bool Village::can_afford(int gold, int mana) {
	return 	m_resources_manager.get_gold() >= gold and 
			m_resources_manager.get_mana() >= mana;
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


int Village::count_building_class(int class_id) {
	int count = 0;
	for (size_t i = 0; i < m_buildings.size(); i++) {
		if (m_buildings[i]->get_class_id() == class_id) {
			count++;
		}
	}
	return count;
}

void Village::buy(std::shared_ptr<Building> building) {
	if (can_afford(building->get_gold_cost(0), building->get_mana_cost(0))) {
		m_resources_manager.add_gold(-building->get_gold_cost(0));
		m_resources_manager.add_mana(-building->get_mana_cost(0));
		add_building(building);
	}
}

std::string Village::get_save_string() {
	std::string res = "";
	for (size_t i = 0; i < m_buildings.size(); i++) {
		res += "Village " + m_buildings[i]->get_save_string() + "\n";
	}
	res += "Village Gold " + std::to_string((int)m_resources_manager.get_gold()) + "\n";
	res += "Village Mana " + std::to_string((int)m_resources_manager.get_mana()) + "\n";
	return res;
}

void Village::parse_save_line(std::string line) {
	if (not line.compare(0, 9, "TownHall ")) {
		std::shared_ptr<TownHall> building = std::make_shared<TownHall>(*this, m_game_manager);
		building->restore_state(line.substr(9, line.length() - 9));
		add_building(building);
	}
	if (not line.compare(0, 9, "GoldTank ")) {
		std::shared_ptr<GoldTank> building = std::make_shared<GoldTank>(*this, m_game_manager);
		building->restore_state(line.substr(9, line.length() - 9));
		add_building(building);
	}
	if (not line.compare(0, 9, "GoldMine ")) {
		std::shared_ptr<GoldMine> building = std::make_shared<GoldMine>(*this, m_game_manager);
		building->restore_state(line.substr(9, line.length() - 9));
		add_building(building);
	}
	if (not line.compare(0, 9, "ManaMill ")) {
		std::shared_ptr<ManaMill> building = std::make_shared<ManaMill>(*this, m_game_manager);
		building->restore_state(line.substr(9, line.length() - 9));
		add_building(building);
	}
	if (not line.compare(0, 9, "ManaTank ")) {
		std::shared_ptr<ManaTank> building = std::make_shared<ManaTank>(*this, m_game_manager);
		building->restore_state(line.substr(9, line.length() - 9));
		add_building(building);
	}
	if (not line.compare(0, 6, "Tower ")) {
		std::shared_ptr<Tower> building = std::make_shared<Tower>(*this, m_game_manager);
		building->restore_state(line.substr(6, line.length() - 6));
		add_building(building);
	}

	if (not line.compare(0, 5, "Gold ")) {
		int gold;
		sscanf(line.substr(5, line.length() - 5).c_str(), "%d", &gold);
		m_resources_manager.add_gold(gold);
	}

	if (not line.compare(0, 5, "Mana ")) {
		int mana;
		sscanf(line.substr(5, line.length() - 5).c_str(), "%d", &mana);
		m_resources_manager.add_mana(mana);
	}

}