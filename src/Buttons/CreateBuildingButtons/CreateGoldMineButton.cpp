#include "Buttons/CreateBuildingButtons/CreateGoldMineButton.hpp"

#include "GameManager.hpp"
#include "Buildings/GoldMine.hpp"
#include "Buildings/Building.hpp"

CreateGoldMineButton::CreateGoldMineButton(GameManager &game_manager, Village &village) : 
		CreateBuildingButton(game_manager, game_manager.get_window_manager().get_assets_manager().get_gold_mine_texture(), village, Building::GOLDMINE_ID, GoldMine::MAX_OCCURENCES,
			0, GoldMine::COSTS[0]) {}

void CreateGoldMineButton::on_click() {
	m_village.buy(std::make_shared<GoldMine>(m_village, m_game_manager));
}