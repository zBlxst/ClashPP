#pragma once

#include "Troops/Troop.hpp"

class Hero : public Troop {

protected:
	int m_level;
	int m_energy;

	int m_base_attack;
	int m_base_max_hp;

	int m_attack_growth;
	int m_max_hp_growth;

public:
	Hero(GameManager &game_manager, sf::Texture &texture, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents, int max_hp, int attack, int attack_speed, int range, int move_speed, int size_in_blocks, int attack_growth, int max_hp_growth);
	virtual void attack(std::shared_ptr<Troop> target);
	virtual void cast_ability() = 0;
	virtual void start();
	bool is_hero();
	void display();
	void update_stats();



};