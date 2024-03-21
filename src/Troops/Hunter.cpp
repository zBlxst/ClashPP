#include "Troops/Hunter.hpp"

#include "GameManager.hpp"

Hunter::Hunter(GameManager &game_manager, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents) : 
	Troop(game_manager, game_manager.get_window_manager().get_assets_manager().get_hunter_texture(), army, opponents, 380, 84, 1000, 3, 20, false, 1) {}
