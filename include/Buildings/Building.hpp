#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include <thread>
#include <memory>

#include "Clickable.hpp"

class Village;
class GameManager;

class BuildingButton;
class Troop;
class Army;

class Building : public Clickable {


protected:

	int m_id;
	int m_class_id;

	GameManager &m_game_manager;
	Village &m_village;
	int m_level;
	int m_level_max;
	int m_max_hp;

	int m_size_in_blocks;

	int m_position_in_village_i;
	int m_position_in_village_j;

	bool m_moving;
	bool m_selected;

	bool m_upgrading;
	double m_upgrade_time;
	double m_upgrade_step;

	sf::Text m_text_upgrade_time;

	std::shared_ptr<Troop> m_troop_component;

	std::vector<std::shared_ptr<BuildingButton>> m_buttons;

	std::shared_ptr<std::thread> m_upgrading_thread;
	static void upgrade_thread_function(Building &obj);

	static constexpr double DEBUG_MULTIPLIER_TIME = 100;


public:

	static constexpr int TOWNHALL_ID = 0;
	static constexpr int GOLDMINE_ID = 1;
	static constexpr int GOLDTANK_ID = 2;
	static constexpr int MANAMILL_ID = 3;
	static constexpr int MANATANK_ID = 4;
	static constexpr int    TOWER_ID = 5;

	static int max_id;

	Building(Village &village, GameManager &game_manager, sf::Texture &texture);

	int m_ghost_position_in_village_i; // Used to position the building and check whether it intersects an other building or not
	int m_ghost_position_in_village_j; 

	int get_id();
	int get_class_id();

	void display_ghost();
	void display();
	bool can_lock();


	virtual float get_gold_tank_capacity();
	virtual float get_mana_tank_capacity();

	virtual float get_gold_cost();
	virtual float get_mana_cost();
	virtual float get_gold_cost(int level);
	virtual float get_mana_cost(int level);

	virtual void level_up();
	int get_level();
	virtual void update_stats();

	virtual void start_upgrade();

	void on_select();
	void on_unselect();

	virtual void interact();
	
	bool can_upgrade();

	virtual void print_infos();
	virtual std::string get_class_name() = 0;

	virtual void update_sprite();
	void add_button(std::shared_ptr<BuildingButton> button);

	void on_click();

	GameManager& get_game_manager();

	int get_position_in_village_i();
	int get_position_in_village_j();
	void set_position_in_village(int i, int j);
	void set_ghost_position_in_village(int i, int j);
	void lock_position();


	bool intersect(Building &other);
	bool ghost_intersect(Building &other);


	int get_size();

	virtual std::shared_ptr<Troop> get_troop_component(std::shared_ptr<Army> army, std::shared_ptr<Army> opponents);


	bool is_position_relative();
	void start_moving();
	void stop_moving();

};

inline int Building::max_id = 0;