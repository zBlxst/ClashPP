#pragma once

#include "ResourceGenerator.hpp"
#include <thread>
#include <memory>
#include "GameManager.hpp"

class GoldMine : public ResourceGenerator {

public:
	GoldMine(Village &village, GameManager &game_manager);

	float get_gold_production();
	float get_gold_capacity();

	float get_mana_cost();


	virtual void update_stats();
	void print_infos();
	std::string get_class_name();

	void interact();



};