#pragma once

#include "Buttons/BuildingButtons/BuildingButton.hpp"


class UpgradeButton : public BuildingButton {

public:
	UpgradeButton(Building &building, GameManager &game_manager);
	void on_click();
	void update_sprite();



};