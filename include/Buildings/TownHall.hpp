#pragma once

#include "Building.hpp"

class Village;
class GameManager;

class TownHall : public Building {

public:
	static constexpr int MAX_LEVEL = 5;
	static constexpr int SIZE = 4;
	static constexpr double COSTS[MAX_LEVEL+1] = {-1, 1700, 5000, 10000, 21000, 36000};
	static constexpr double UPGRADE_TIMES[MAX_LEVEL+1] = {0, 120, 600, 1800, 3600, 7200};
	static constexpr double MAX_HPS[MAX_LEVEL+1] = {0, 4500, 5500, 6500, 7500, 9000};
	static constexpr std::array<int, MAX_LEVEL+1> MAX_OCCURENCES = {1, 1, 1, 1, 1, 1};


private:
	float m_cost;


public:
	TownHall(Village &village, GameManager &game_manager);
	float get_gold_cost();
	float get_gold_cost(int level);
	void update_stats();
	std::string get_class_name();
};