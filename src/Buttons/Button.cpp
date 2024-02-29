#include "Buttons/Button.hpp"

Button::Button(WindowManager &window_manager, sf::Texture &texture) : Clickable(window_manager, texture, false, false) {}

bool Button::is_position_relative() {
	return false;
}

void Button::load() {
	set_visible(true);
	set_active(true);
}

void Button::unload() {
	set_visible(false);
	set_active(false);
}