#include "Clickable.hpp"


Clickable::Clickable(WindowManager &window_manager, sf::Texture &texture) : Displayable(window_manager, texture) {}

bool Clickable::is_clicked(int pos_x, int pos_y) {
	return 	pos_x < m_position_x + m_size_x and
			pos_x > m_position_x and
			pos_y < m_position_y + m_size_y and
			pos_y > m_position_y;
}

