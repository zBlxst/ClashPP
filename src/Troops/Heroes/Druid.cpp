#include "Troops/Heroes/Druid.hpp"

#include "GameManager.hpp"
#include "Army.hpp"

Druid::Druid(GameManager &game_manager, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents) :
	Hero(game_manager, game_manager.get_window_manager().get_assets_manager().get_druid_texture(), army, opponents, 1600, 205, 1000, 3, 15, 2, 10, 80) {}

void Druid::cast_ability() {
	std::vector<std::shared_ptr<Troop>> targets = m_army->get_troops();
	for (size_t i = 0; i < targets.size(); i++) {
		if (targets[i]->is_alive()) {
			targets[i]->heal(2*m_attack);
		}
	}
}