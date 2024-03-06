#pragma once

#include "Buttons/CreateBuildingButtons/CreateBuildingButton.hpp"


class Village;
class GameManager;

class CreateManaMillButton : public CreateBuildingButton {


public:
	CreateManaMillButton(GameManager &game_manager, Village &village);
	void on_click();

};