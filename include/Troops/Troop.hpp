#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Displayable.hpp"
#include <thread>


class Army;
class WindowManager;
class GameManager;

class Troop : public Displayable, public std::enable_shared_from_this<Troop> {

protected:

	GameManager &m_game_manager;

	std::shared_ptr<Army> m_army;
	std::shared_ptr<Army> m_opponents;
	std::shared_ptr<Troop> m_target;

	bool m_alive;
	int m_max_hp;
	int m_hp;
	int m_attack;
	int m_attack_speed;
	int m_range;
	int m_move_speed;
	bool m_passive;
	int m_size_in_blocks;

	std::shared_ptr<std::thread> m_live_thread;
	static void live_thread_function(Troop &troop);

public:
	Troop(GameManager &game_manager, sf::Texture &texture, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents, int max_hp, int attack, int attack_speed, int range, int move_speed, bool passive, int size_in_blocks);
	void recv_damage(int amount, std::shared_ptr<Troop> source);
	void lose_hp(int amount);
	void heal(int amount);
	virtual void attack(std::shared_ptr<Troop> target);
	void die();
	void find_target();
	bool is_alive();
	int distance(std::shared_ptr<Troop> troop);
	bool is_in_range(std::shared_ptr<Troop> troop);
	void move_to_target();
	void attack_target();

	bool is_position_relative();
	virtual bool is_hero();


	virtual void display();
	virtual void start();
	void stop();
	bool is_passive();
	void update_sprite();

	GameManager& get_game_manager();




};