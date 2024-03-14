#include "Displayable.hpp"

#include "WindowManager.hpp"
#include <iostream>


Displayable::Displayable(WindowManager &window_manager, sf::Texture &texture, bool visible) : 
	m_position_x(0), m_position_y(0), m_size_x(0), m_size_y(0), m_is_debugging(false), m_visible(visible), m_window_manager(window_manager), m_texture(texture) {

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
		if (scale_x != 1 or scale_y != 1) printf("%f, %f\n", scale_x, scale_y);
		m_sprite.scale(scale_x, scale_y);
	}

}

void Displayable::display() {
	if (m_is_debugging) {
		std::cout << "Position : " << m_position_x << " " << m_position_y << std::endl;
		std::cout << "Size : " << m_size_x << " " << m_size_y << std::endl;
	}
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