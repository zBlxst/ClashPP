#include "Buttons/BuildingButtons/CollectGoldButton.hpp"

#include "GameManager.hpp"

CollectGoldButton::CollectGoldButton(ResourceGenerator &resource_generator, GameManager &game_manager) :
		CollectResourceButton(resource_generator, game_manager, game_manager.get_window_manager().get_assets_manager().get_collect_gold_texture()) {}