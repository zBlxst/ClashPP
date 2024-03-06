#include "Buttons/CreateBuildingButtons/CreateManaMillButton.hpp"

#include "GameManager.hpp"
#include "Buildings/ManaMill.hpp"
#include "Buildings/Building.hpp"

CreateManaMillButton::CreateManaMillButton(GameManager &game_manager, Village &village) : 
		CreateBuildingButton(game_manager, game_manager.get_window_manager().get_assets_manager().get_mana_mill_texture(), village, Building::MANAMILL_ID) {}

void CreateManaMillButton::on_click() {
	m_village.add_building(std::make_shared<ManaMill>(m_village, m_game_manager));
}