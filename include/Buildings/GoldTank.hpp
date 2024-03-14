#pragma once

#include "Tank.hpp"

class Village;
class GameManager;

class GoldTank : public Tank {

private:

public:
	GoldTank(Village &village, GameManager &game_manager);
	float get_gold_tank_capacity();
	float get_mana_cost();
	float get_mana_cost(int level);
	void print_infos();
	std::string get_class_name();





};