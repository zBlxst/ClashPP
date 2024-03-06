#pragma once

#include "Buttons/CreateBuildingButtons/CreateBuildingButton.hpp"


class Village;
class GameManager;

class CreateManaTankButton : public CreateBuildingButton {


public:
	CreateManaTankButton(GameManager &game_manager, Village &village);
	void on_click();

};