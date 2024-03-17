#include "Clickable.hpp"
#include "WindowManager.hpp"

Clickable::Clickable(WindowManager &window_manager, sf::Texture &texture, bool active, bool visible) : Displayable(window_manager, texture, visible), m_active(active) {}

bool Clickable::is_clicked(int pos_x, int pos_y) {
	if (is_position_relative()) {
		pos_x += m_window_manager.get_camera().get_x();
		pos_y += m_window_manager.get_camera().get_y();
	}
	return 	m_active and
			pos_x < m_position_x + m_size_x and
			pos_x > m_position_x and
			pos_y < m_position_y + m_size_y and
			pos_y > m_position_y;
}

bool Clickable::get_active() {
	return m_active;
}
void Clickable::set_active(bool value) {
	m_active = value;
}
