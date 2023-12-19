#pragma once

#include <vector>
#include <memory>

#include "ResourcesManager.hpp"

class Building;
class GameManager;
class TownHall;

class Village {

private:
	GameManager &m_game_manager;
	std::shared_ptr<TownHall> m_town_hall;
	std::vector<std::shared_ptr<Building>> m_buildings;
	ResourcesManager m_resources_manager;

public:
	static constexpr int SIZE_IN_BLOCKS = 36;

	explicit Village(GameManager &game_manager);
	void add_building(std::shared_ptr<Building> b);
	void update();

	std::vector<std::shared_ptr<Building>>& get_buildings();
	ResourcesManager& get_resources_manager();


	int get_town_hall_level();
	void set_town_hall(std::shared_ptr<TownHall> th);

	bool ghost_intersect(Building &ghost);
	void find_free_room(Building &building);
};