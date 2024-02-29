#pragma once

#include "SFML/Graphics.hpp"

class WindowManager;

class Displayable {

protected:
	int m_position_x;
	int m_position_y;
	int m_size_x;
	int m_size_y;

	bool m_visible;

	WindowManager &m_window_manager;
	sf::Sprite m_sprite;



public:
	Displayable(WindowManager &window_manager, sf::Texture &texture, bool visible);
	void display();
	virtual void update_sprite();

	virtual bool is_position_relative() = 0;
	void move(int x, int y);

	bool get_visible();
	void set_visible(bool value);





};