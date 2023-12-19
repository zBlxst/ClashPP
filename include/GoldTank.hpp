#pragma once

#include "Tank.hpp"

class Village;

class GoldTank : public Tank {

private:

public:
	GoldTank(Village &village, GameManager &game_manager);
	float get_gold_tank_capacity();
	float get_mana_cost();
	void print_infos();
	std::string get_class_name();





};