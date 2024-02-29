#include "Displayable.hpp"

#include "WindowManager.hpp"
#include <iostream>


Displayable::Displayable(WindowManager &window_manager, sf::Texture &texture, bool visible) : 
	m_position_x(0), m_position_y(0), m_size_x(0), m_size_y(0), m_visible(visible), m_window_manager(window_manager) {
	m_sprite.setTexture(texture);
}

void Displayable::update_sprite() {
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	float scale_x = (float)m_size_x/bounds.width;
	float scale_y = (float)m_size_y/bounds.height;
	m_sprite.scale(scale_x, scale_y);
}

void Displayable::display() {
	if (m_visible) {
		m_sprite.setPosition(m_position_x, m_position_y);
		sf::RenderWindow &window = m_window_manager.get_window();
		window.draw(m_sprite);
	}
}

void Displayable::move(int x, int y) {
	m_position_x = x;
	m_position_y = y;
}

bool Displayable::get_visible() {
	return m_visible;
}
void Displayable::set_visible(bool value) {
	m_visible = value;
}
