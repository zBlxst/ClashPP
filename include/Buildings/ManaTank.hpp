#pragma once

#include "Tank.hpp"

class Village;
class GameManager;

class ManaTank : public Tank {

private:

public:
	ManaTank(Village &village, GameManager &game_manager);
	float get_mana_tank_capacity();
	float get_gold_cost();
	void print_infos();
	std::string get_class_name();


};