#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.hpp"

#include <vector>
#include <memory>

class GameManager;
class Displayable;
class Clickable;

class WindowManager {

private:
	GameManager &m_game_manager;
	AssetsManager m_assets_manager;

	std::vector<std::shared_ptr<Displayable>> m_displayables;
	std::vector<std::shared_ptr<Clickable>> m_clickables;

	int m_width;
	int m_height;

	int m_width_block;
	int m_height_block;

	sf::Text m_text_gold;
	sf::Text m_text_mana;

	sf::RenderWindow m_window;

public:
	WindowManager(int width, int height, GameManager &game_manager);
	void start();
	void stop();

	void display();
	void add_displayable(std::shared_ptr<Displayable> displayable);
	void add_clickable(std::shared_ptr<Clickable> clickable);
	void update_sprites();
	void manage_events();

	int get_width_block();
	int get_height_block();


	sf::RenderWindow& get_window();
	AssetsManager &get_assets_manager();





};