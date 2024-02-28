#pragma once

#include <SFML/Graphics.hpp>
#include "Scenes/Scene.hpp"


class WindowManager;
class GameManager;

class VillageScene : public Scene {

private:
	GameManager &m_game_manager;

	sf::Text m_text_gold;
	sf::Text m_text_mana;


public:
	VillageScene(WindowManager &window_manager, GameManager &game_manager, bool visible);

	void load();
	void unload();

	void display();

	void manage_event(sf::Event event);


};