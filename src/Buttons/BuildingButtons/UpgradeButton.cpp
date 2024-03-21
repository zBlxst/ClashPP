#include "Buttons/BuildingButtons/UpgradeButton.hpp"

#include "GameManager.hpp"
#include "Buildings/Building.hpp"


UpgradeButton::UpgradeButton(Building &building, GameManager &game_manager) : 
		BuildingButton(building, game_manager, game_manager.get_window_manager().get_assets_manager().get_building_upgrade_texture()) {

	m_cost_text.setFont(m_window_manager.get_assets_manager().get_gold_and_mana_font());
}

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

void UpgradeButton::display() {
	BuildingButton::display();
	if (m_visible) {

		int text_size = m_window_manager.get_height_block();

		m_cost_text.setFont(m_window_manager.get_assets_manager().get_gold_and_mana_font());
		m_cost_text.setCharacterSize(text_size);
		if (m_building.get_gold_cost() > 0) {
			m_cost_text.setString("Gold : " + std::to_string((int)m_building.get_gold_cost()));
		} else if (m_building.get_mana_cost() > 0){
			m_cost_text.setString("Mana : " + std::to_string((int)m_building.get_mana_cost()));
		} else {
			printf("fjezijoize\n");
			m_cost_text.setString("");
		}
		if (!m_building.can_upgrade()) {
			m_cost_text.setFillColor(sf::Color(100, 100, 100));
		} else {
			m_cost_text.setFillColor(sf::Color(255, 255, 255));

		}

		int pos_cost_x = get_x() + get_width() / 2 - m_cost_text.getGlobalBounds().width/2;
		int pos_cost_y = get_y() + get_height();
		m_cost_text.setPosition(pos_cost_x, pos_cost_y);

		m_window_manager.get_window().draw(m_cost_text);

	}
}