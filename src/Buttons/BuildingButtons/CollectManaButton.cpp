#include "Buttons/BuildingButtons/CollectManaButton.hpp"

#include "GameManager.hpp"


CollectManaButton::CollectManaButton(ResourceGenerator &resource_generator, GameManager &game_manager) :
		CollectResourceButton(resource_generator, game_manager, game_manager.get_window_manager().get_assets_manager().get_collect_mana_texture()) {}