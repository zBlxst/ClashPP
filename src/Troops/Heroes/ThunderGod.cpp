#include "Troops/Heroes/ThunderGod.hpp"

#include "GameManager.hpp"
#include "Army.hpp"

ThunderGod::ThunderGod(GameManager &game_manager, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents) :
	Hero(game_manager, game_manager.get_window_manager().get_assets_manager().get_thunder_god_texture(), army, opponents, 1600, 220, 1000, 0, 17, 2, 11, 80) {}

void ThunderGod::cast_ability() {
	std::vector<std::shared_ptr<Troop>> targets = m_opponents->get_troops();
	for (size_t i = 0, hit = 0; i < targets.size() && hit < 5; i++) {
		if (targets[i]->is_alive()) {
			targets[i]->recv_damage(2*m_attack, this->shared_from_this());
			hit += 1;
		}
	}
}