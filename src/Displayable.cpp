#include "Displayable.hpp"

#include "WindowManager.hpp"
#include <iostream>
#include <cmath>


Displayable::Displayable(WindowManager &window_manager, sf::Texture &texture, bool visible) : 
	m_position_x(0), m_position_y(0), m_size_x(0), m_size_y(0), m_visible(visible), m_window_manager(window_manager), m_texture(texture) {

	reload_texture();
}

void Displayable::reload_texture() {
	m_sprite.setTexture(m_texture);
}

void Displayable::update_sprite() {
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	if (m_size_x != 0 and m_size_y != 0) {
		float scale_x = (float)m_size_x/bounds.width;
		float scale_y = (float)m_size_y/bounds.height;
		m_sprite.scale(scale_x, scale_y);
	}

}

void Displayable::display() {
	if (m_visible) {
		if (is_position_relative()) {
			m_sprite.setPosition(m_position_x - m_window_manager.get_camera().get_x(), m_position_y - m_window_manager.get_camera().get_y());	
		} else {
			m_sprite.setPosition(m_position_x, m_position_y);
		}
		sf::RenderWindow &window = m_window_manager.get_window();
		window.draw(m_sprite);
	}
}

void Displayable::move(int x, int y) {
	m_position_x = x;
	m_position_y = y;
}

void Displayable::move_rel(int x, int y) {
	m_position_x += x;
	m_position_y += y;
}



void Displayable::resize(int x, int y) {
	m_size_x = x;
	m_size_y = y;
}

int Displayable::get_width() {
	return m_size_x;
}

int Displayable::get_height() {
	return m_size_y;
}

bool Displayable::get_visible() {
	return m_visible;
}

void Displayable::set_visible(bool value) {
	m_visible = value;
}

sf::Texture& Displayable::get_texture() {
	return m_texture;
}

int Displayable::get_x() {
	return m_position_x;
}

int Displayable::get_y() {
	return m_position_y;
}

int Displayable::get_center_x() {
	return m_position_x + m_size_x / 2;
}

int Displayable::get_center_y() {
	return m_position_y + m_size_y / 2;
}