#pragma once

#include "Buttons/CreateBuildingButtons/CreateBuildingButton.hpp"


class Village;
class GameManager;

class CreateTowerButton : public CreateBuildingButton {


public:
	CreateTowerButton(GameManager &game_manager, Village &village);
	void on_click();

};