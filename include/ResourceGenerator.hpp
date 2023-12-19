#pragma once

#include "Building.hpp"

class ResourceGenerator : public Building {

protected:
	float m_cost;

	float m_production;
	float m_stored;
	float m_capacity;

	static constexpr double DEBUG_MULTIPLIER = 600;

	static constexpr int SIZE = 3;

	static constexpr int MAX_LEVEL = 5;
	static constexpr double CAPACITIES[MAX_LEVEL+1] = {0, 10000, 13000, 16000, 19000, 22000};
	static constexpr double PRODUCTIONS[MAX_LEVEL+1] = {0, 2100, 2200, 2300, 2400, 2500};
	static constexpr double COSTS[MAX_LEVEL+1] = {240, 1100, 3000, 6000, 13000, 22000};

public:
	ResourceGenerator(Village &village, GameManager &game_manager, sf::Texture &texture);
	virtual void update_stats();
	virtual void print_infos();

	float get_stored();
	void add_stored(float amount);
	float get_production();
	float get_capacity();

};