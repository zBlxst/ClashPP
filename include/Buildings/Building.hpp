#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <thread>
#include <memory>

#include "Clickable.hpp"

class Village;
class GameManager;


class Building : public Clickable {


protected:

	int m_id;

	GameManager &m_game_manager;
	Village &m_village;
	int m_level;
	int m_level_max;

	int m_size_in_blocks;

	int m_position_in_village_i;
	int m_position_in_village_j;

	bool m_upgrading;
	double m_upgrade_time;
	double m_upgrade_step;

	std::shared_ptr<std::thread> m_upgrading_thread;
	static void upgrade_thread_function(Building &obj);

	static constexpr double DEBUG_MULTIPLIER_TIME = 100;


public:


	static int max_id;

	Building(Village &village, GameManager &game_manager, sf::Texture &texture);

	int m_ghost_position_in_village_i; // Used to position the building and check whether it intersects an other building or not
	int m_ghost_position_in_village_j; 

	int get_id();


	virtual float get_gold_tank_capacity();
	virtual float get_mana_tank_capacity();

	virtual float get_gold_cost();
	virtual float get_mana_cost();

	virtual void level_up();
	int get_level();
	virtual void update_stats();

	virtual void start_upgrade();

	virtual void interact();

	virtual void print_infos();
	virtual std::string get_class_name() = 0;

	virtual void update_sprite();

	void on_click();

	GameManager& get_game_manager();

	int get_position_in_village_i();
	int get_position_in_village_j();
	void set_position_in_village();
	void lock_position();


	bool intersect(Building &other);
	bool ghost_intersect(Building &other);


	int get_size();



	bool is_position_relative();

};

inline int Building::max_id = 0;