#pragma once

#include "SFML/Graphics.hpp"

class WindowManager;

class Displayable {

protected:
	int m_position_x;
	int m_position_y;
	int m_size_x;
	int m_size_y;

	bool m_is_debugging;

	bool m_visible;

	WindowManager &m_window_manager;
	sf::Sprite m_sprite;
	sf::Texture &m_texture;


public:
	Displayable(WindowManager &window_manager, sf::Texture &texture, bool visible);
	virtual void display();
	virtual void update_sprite();
	void reload_texture();

	virtual bool is_position_relative() = 0;
	void move(int x, int y);
	void resize(int x, int y);

	int get_width();
	int get_height();

	bool get_visible();
	void set_visible(bool value);

	sf::Texture& get_texture();







};