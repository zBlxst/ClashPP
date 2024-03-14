#include "Buttons/CreateBuildingButtons/CreateManaTankButton.hpp"

#include "GameManager.hpp"
#include "Buildings/ManaTank.hpp"
#include "Buildings/Building.hpp"

CreateManaTankButton::CreateManaTankButton(GameManager &game_manager, Village &village) : 
		CreateBuildingButton(game_manager, game_manager.get_window_manager().get_assets_manager().get_mana_tank_texture(), village, Building::MANATANK_ID, ManaTank::MAX_OCCURENCES,
			ManaTank::COSTS[0], 0) {}

void CreateManaTankButton::on_click() {
	m_village.buy(std::make_shared<ManaTank>(m_village, m_game_manager));
}