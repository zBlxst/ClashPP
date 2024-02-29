#pragma once

#include "Buttons/BuildingButtons/CollectResourceButton.hpp"


class CollectGoldButton : public CollectResourceButton {


public:
	CollectGoldButton(ResourceGenerator &resource_generator, GameManager &game_manager);
};