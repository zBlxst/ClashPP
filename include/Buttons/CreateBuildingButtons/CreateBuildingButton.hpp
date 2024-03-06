#pragma once

#include "Buttons/Button.hpp"


class Village;
class GameManager;

class CreateBuildingButton : public Button {

protected:
	Village &m_village;
	GameManager &m_game_manager;
	int m_class_id;

public:
	CreateBuildingButton(GameManager &game_manager, sf::Texture &texture, Village &village, int class_id);
};