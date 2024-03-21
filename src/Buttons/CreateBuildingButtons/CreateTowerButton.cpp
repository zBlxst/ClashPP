#include "Buttons/CreateBuildingButtons/CreateTowerButton.hpp"

#include "GameManager.hpp"
#include "Buildings/Tower.hpp"
#include "Buildings/Building.hpp"

CreateTowerButton::CreateTowerButton(GameManager &game_manager, Village &village) : 
		CreateBuildingButton(game_manager, game_manager.get_window_manager().get_assets_manager().get_tower_texture(), village, Building::TOWER_ID, Tower::MAX_OCCURENCES,
			Tower::COSTS[0], 0) {}

void CreateTowerButton::on_click() {
	m_village.buy(std::make_shared<Tower>(m_village, m_game_manager));
}