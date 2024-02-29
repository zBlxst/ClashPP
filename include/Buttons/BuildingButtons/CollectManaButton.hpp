#pragma once

#include "Buttons/BuildingButtons/CollectResourceButton.hpp"

class CollectManaButton : public CollectResourceButton {


public:
	CollectManaButton(ResourceGenerator &resource_generator, GameManager &game_manager);
};