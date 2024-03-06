#include "Buttons/CreateBuildingButtons/CreateGoldTankButton.hpp"

#include "GameManager.hpp"
#include "Buildings/GoldTank.hpp"
#include "Buildings/Building.hpp"

CreateGoldTankButton::CreateGoldTankButton(GameManager &game_manager, Village &village) : 
		CreateBuildingButton(game_manager, game_manager.get_window_manager().get_assets_manager().get_gold_tank_texture(), village, Building::GOLDTANK_ID) {}

void CreateGoldTankButton::on_click() {
	m_village.add_building(std::make_shared<GoldTank>(m_village, m_game_manager));
}