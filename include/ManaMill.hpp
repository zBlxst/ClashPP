#pragma once

#include "ResourceGenerator.hpp"
#include <thread>
#include <memory>
#include "GameManager.hpp"

class ManaMill : public ResourceGenerator {

private:
	std::shared_ptr<std::thread> m_production_thread;

public:
	ManaMill(Village &village, GameManager &game_manager);

	float get_mana_production();
	float get_mana_capacity();
	float get_gold_cost();

	static void production_thread_function(ManaMill &obj);

	virtual void update_stats();
	void print_infos();
	std::string get_class_name();

	void interact();



};