#pragma once

#include "Buttons/BuildingButtons/BuildingButton.hpp"

class ResourceGenerator;

class CollectResourceButton : public BuildingButton {

protected:
	ResourceGenerator &m_resource_generator;


public:
	CollectResourceButton(ResourceGenerator &resource_generator, GameManager &game_manager, sf::Texture &texture);
	void on_click();
	void update_sprite();
};