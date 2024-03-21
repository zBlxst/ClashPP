#pragma once

#include "Building.hpp"
#include "Buildings/TownHall.hpp"
#include <memory>
#include <thread>

class Village;
class GameManager;

class ResourceGenerator : public Building {

public:
	static constexpr int MAX_LEVEL = 5;
	static constexpr double CAPACITIES[MAX_LEVEL+1] = {0, 10000, 13000, 16000, 19000, 22000};
	static constexpr double PRODUCTIONS[MAX_LEVEL+1] = {0, 2100, 2200, 2300, 2400, 2500};
	static constexpr double COSTS[MAX_LEVEL+1] = {240, 1100, 3000, 6000, 13000, 22000};
	static constexpr double UPGRADE_TIMES[MAX_LEVEL+1] = {10, 60, 300, 900, 1800, 3600};
	static constexpr double MAX_HPS[MAX_LEVEL+1] = {0, 2500, 3000, 3500, 4000, 4500};
	static constexpr std::array<int, TownHall::MAX_LEVEL+1> MAX_OCCURENCES = {3, 3, 3, 3, 3, 3};

protected:
	float m_cost;

	float m_production;
	float m_stored;
	float m_capacity;

	static constexpr double DEBUG_MULTIPLIER = 600;

	static constexpr int SIZE = 3;



	std::shared_ptr<std::thread> m_production_thread;
	static void production_thread_function(ResourceGenerator &obj);

public:
	ResourceGenerator(Village &village, GameManager &game_manager, sf::Texture &texture);
	virtual void update_stats();
	virtual void print_infos();

	virtual void collect() = 0;

	float get_stored();
	void add_stored(float amount);
	float get_production();
	float get_capacity();

	std::string get_save_string();
	void restore_state(std::string);

};