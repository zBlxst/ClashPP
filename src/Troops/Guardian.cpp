#include "Troops/Guardian.hpp"

#include "GameManager.hpp"

Guardian::Guardian(GameManager &game_manager, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents) : 
	Troop(game_manager, game_manager.get_window_manager().get_assets_manager().get_guardian_texture(), army, opponents, 350, 75, 1000, 0, 10, false, 1) {}

