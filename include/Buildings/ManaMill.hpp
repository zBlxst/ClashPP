#pragma once

#include "ResourceGenerator.hpp"
#include <thread>
#include <memory>

class Village;
class GameManager;

class ManaMill : public ResourceGenerator {

public:
	ManaMill(Village &village, GameManager &game_manager);

	float get_mana_production();
	float get_mana_capacity();
	float get_gold_cost();


	virtual void update_stats();
	void print_infos();
	std::string get_class_name();

	void interact();



};