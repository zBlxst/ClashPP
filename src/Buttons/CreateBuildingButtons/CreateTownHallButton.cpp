#include "Buttons/CreateBuildingButtons/CreateTownHallButton.hpp"

#include "GameManager.hpp"
#include "Buildings/TownHall.hpp"
#include "Buildings/Building.hpp"

CreateTownHallButton::CreateTownHallButton(GameManager &game_manager, Village &village) : 
		CreateBuildingButton(game_manager, game_manager.get_window_manager().get_assets_manager().get_town_hall_texture(), village, Building::TOWNHALL_ID, TownHall::MAX_OCCURENCES,
			TownHall::COSTS[0], 0) {}

void CreateTownHallButton::on_click() {
	m_village.buy(std::make_shared<TownHall>(m_village, m_game_manager));
}