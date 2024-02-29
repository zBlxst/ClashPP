#include "Buttons/BuildingButtons/UpgradeButton.hpp"

#include "GameManager.hpp"
#include "Buildings/Building.hpp"


UpgradeButton::UpgradeButton(Building &building, GameManager &game_manager) : 
		BuildingButton(building, game_manager, game_manager.get_window_manager().get_assets_manager().get_building_upgrade_texture()) {}

void UpgradeButton::on_click() {
	m_building.start_upgrade();
}

void UpgradeButton::update_sprite() {
	if (!m_building.can_upgrade()) {
		m_sprite.setColor(sf::Color(100, 100, 100));
	} else {
		m_sprite.setColor(sf::Color(255, 255, 255));
	}
	BuildingButton::update_sprite();
}