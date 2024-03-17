#pragma once

#include <SFML/Graphics.hpp>
#include "AssetsManager.hpp"

#include <vector>
#include <memory> 

#include "Scenes/Scene.hpp"
#include <Scenes/VillageScene.hpp>
#include "Camera.hpp"

class GameManager;
class Displayable;
class Clickable;


class WindowManager {

private:
	GameManager &m_game_manager;
	AssetsManager m_assets_manager;

	std::vector<std::shared_ptr<Displayable>> m_displayables;
	std::vector<std::shared_ptr<Clickable>> m_clickables;

	std::shared_ptr<VillageScene> m_village_scene;
	std::shared_ptr<Scene> m_current_scene;

	int m_width;
	int m_height;

	int m_width_block;
	int m_height_block;

	sf::Text m_text_gold;
	sf::Text m_text_mana;

	sf::RenderWindow m_window;
	Camera m_camera;


public:
	WindowManager(int width, int height, GameManager &game_manager);
	void start();
	void stop();

	void display();
	void manage_events();

	int get_width_block();
	int get_height_block();

	int get_width();
	int get_height();

	std::shared_ptr<Scene> get_current_scene();
	std::shared_ptr<VillageScene> get_village_scene();


	sf::RenderWindow& get_window();
	AssetsManager &get_assets_manager();
	GameManager &get_game_manager();

	Camera &get_camera();




};