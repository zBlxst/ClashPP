#pragma once

#include "Buttons/BuildingButtons/BuildingButton.hpp"


class InfoButton : public BuildingButton {

public:
	InfoButton(Building &building, GameManager &game_manager);
	void on_click();

};