#include "Buttons/BuildingButtons/BuildingButton.hpp"

#include "GameManager.hpp"

BuildingButton::BuildingButton(Building &building, GameManager &game_manager, sf::Texture &texture) : 
		Button(game_manager.get_window_manager(), texture), m_building(building) {
	update_sprite();
}

Building& BuildingButton::get_building() {
	return m_building;
}

void BuildingButton::update_sprite() {
	m_size_x = (int)(0.1*m_window_manager.get_width());
	m_size_y = (int)(0.1*m_window_manager.get_height());
	Button::update_sprite();
} 

void BuildingButton::load(int rank, int amount) {
	int base = (int)(0.5*m_window_manager.get_width()) - (int)((0.5+amount-1)*m_size_x);
	m_position_x = base + 2*rank*m_size_x;
	m_position_y = m_window_manager.get_height() - (int)(3/2*m_size_y);
	Button::load();
}
