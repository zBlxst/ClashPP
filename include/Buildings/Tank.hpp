#pragma once

#include "Building.hpp"
#include "Buildings/TownHall.hpp"

class Village;
class GameManager;

class Tank : public Building {

public:
	static constexpr int MAX_LEVEL = 5;
	static constexpr double CAPACITIES[MAX_LEVEL+1] = {0, 30000, 33000, 39000, 65000, 80000};
	static constexpr double COSTS[MAX_LEVEL+1] = {240, 1100, 3000, 6000, 13000, 22000};
	static constexpr double UPGRADE_TIMES[MAX_LEVEL+1] = {10, 60, 300, 900, 1800, 3600};
	static constexpr std::array<int, TownHall::MAX_LEVEL+1> MAX_OCCURENCES = {3, 3, 3, 3, 3, 3};

protected:
	float m_cost;
	float m_capacity;

	static constexpr int SIZE = 3;


public:
	Tank(Village &village, GameManager &game_manager, sf::Texture &texture);
	virtual void update_stats();
	virtual void print_infos();

};
