#pragma once

#include "Buttons/Button.hpp"
#include <iostream>

class Building;
class GameManager;

class BuildingButton : public Button {

protected:
	Building &m_building;


public:
	BuildingButton(Building &building, GameManager &game_manager, sf::Texture &texture);
	Building &get_building();
	virtual void update_sprite();

	void load(int rank, int amount);

};