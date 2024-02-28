#pragma once

#include <SFML/Graphics.hpp>
#include "Scenes/Scene.hpp"

#include <memory>
#include <optional>

class WindowManager;
class GameManager;
class Building;

class VillageScene : public Scene {

private:
	GameManager &m_game_manager;

	sf::Text m_text_gold;
	sf::Text m_text_mana;

	int m_selected_building_id;

public:
	VillageScene(WindowManager &window_manager, GameManager &game_manager, bool visible);

	void load();
	void unload();

	void display();

	void manage_event(sf::Event event);
	int get_selected_building_id();
	void selected_building(int id);


};