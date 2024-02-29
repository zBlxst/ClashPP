#include "Buttons/BuildingButtons/InfoButton.hpp"

#include "GameManager.hpp"
#include "Buildings/Building.hpp"


InfoButton::InfoButton(Building &building, GameManager &game_manager) : 
		BuildingButton(building, game_manager, game_manager.get_window_manager().get_assets_manager().get_building_info_texture()) {}

void InfoButton::on_click() {
	m_building.print_infos();
}
