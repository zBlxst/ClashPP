#pragma once

#include "Buttons/Button.hpp"
#include "Buildings/TownHall.hpp"
#include <vector>

class Village;
class GameManager;

class CreateBuildingButton : public Button {

protected:
	Village &m_village;
	GameManager &m_game_manager;
	int m_class_id;
	std::array<int, TownHall::MAX_LEVEL+1> m_class_max_element;
	double m_gold_cost;
	double m_mana_cost;

	sf::Text m_amount_text;
	sf::Text m_cost_text;

public:
	CreateBuildingButton(GameManager &game_manager, sf::Texture &texture, Village &village, int class_id, std::array<int, TownHall::MAX_LEVEL+1> class_max_element, double gold_cost, double mana_cost);
	int get_class_id();
	void update_sprite();
	void display();
};