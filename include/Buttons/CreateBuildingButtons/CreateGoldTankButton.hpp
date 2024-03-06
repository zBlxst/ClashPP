#pragma once

#include "Buttons/CreateBuildingButtons/CreateBuildingButton.hpp"


class Village;
class GameManager;

class CreateGoldTankButton : public CreateBuildingButton {


public:
	CreateGoldTankButton(GameManager &game_manager, Village &village);
	void on_click();

};