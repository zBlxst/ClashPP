#pragma once

#include "Buildings/Building.hpp"

class Tower : public Building {

public:
	static constexpr int MAX_LEVEL = 5;
	static constexpr int SIZE = 3;
	static constexpr double COSTS[MAX_LEVEL+1] = {200, 1000, 2000, 3000, 7000, 12000};
	static constexpr double UPGRADE_TIMES[MAX_LEVEL+1] = {10, 60, 300, 900, 1800, 3600};
	static constexpr std::array<int, MAX_LEVEL+1> MAX_OCCURENCES = {3, 3, 3, 3, 3, 3};

	static constexpr double MAX_HPS[MAX_LEVEL+1] = {0, 2700, 3400, 4100, 4800, 5500};
	static constexpr double ATTACKS[MAX_LEVEL+1] = {0, 60, 80, 100, 120, 140};
	static constexpr double RANGES[MAX_LEVEL+1] = {0, 13, 13, 14, 14, 15};
	

private:
	float m_cost;
	double m_attack;
	double m_range;

public:
	Tower(Village &village, GameManager &game_manager);
	float get_gold_cost();
	float get_gold_cost(int level);
	void update_stats();
	std::string get_class_name();

	std::shared_ptr<Troop> get_troop_component(std::shared_ptr<Army> army, std::shared_ptr<Army> opponents);



};