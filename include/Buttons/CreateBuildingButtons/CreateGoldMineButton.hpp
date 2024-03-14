#pragma once

#include "Buttons/CreateBuildingButtons/CreateBuildingButton.hpp"


class Village;
class GameManager;

class CreateGoldMineButton : public CreateBuildingButton {


public:
	CreateGoldMineButton(GameManager &game_manager, Village &village);
	void on_click();
};