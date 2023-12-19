#pragma once

#include "Building.hpp"

class Village;

class TownHall : public Building {

private:
	static constexpr int SIZE = 4;
	static constexpr int MAX_LEVEL = 5;
	static constexpr double COSTS[MAX_LEVEL+1] = {0, 1700, 5000, 10000, 21000, 36000};

	float m_cost;


public:
	TownHall(Village &village, GameManager &game_manager);
	float get_gold_cost();
	void update_stats();
	std::string get_class_name();
};