#pragma once

#include <SFML/Graphics.hpp>
#include "Scenes/Scene.hpp"
#include "Scenes/ShopScene.hpp"

#include <memory>
#include <optional>

class WindowManager;
class GameManager;
class Building;
class Village;

class VillageScene : public Scene {

private:
	GameManager &m_game_manager;
	Village &m_village;

	ShopScene m_shop_scene;


	sf::Text m_text_gold;
	sf::Text m_text_mana;

	int m_selected_building_id;


public:
	VillageScene(WindowManager &window_manager, GameManager &game_manager, Village &village, bool visible);

	void load();

	void display();
	void open_shop();

	bool manage_event(sf::Event event);
	int get_selected_building_id();
	void select_building(Building &building);
	void unselect_building();
	Village& get_village();


};