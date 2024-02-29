#pragma once

#include "Clickable.hpp"

class Button : public Clickable {

protected:

public:
	Button(WindowManager &window_manager, sf::Texture &texture);
	bool is_position_relative();

	void load();
	void unload();
};