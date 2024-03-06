#pragma once

#include "Buttons/CreateBuildingButtons/CreateBuildingButton.hpp"


class Village;
class GameManager;

class CreateTownHallButton : public CreateBuildingButton {


public:
	CreateTownHallButton(GameManager &game_manager, Village &village);
	void on_click();

};