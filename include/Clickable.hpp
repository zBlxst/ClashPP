#pragma once

#include "Displayable.hpp"

class Clickable : public Displayable {

private:


public:
	Clickable(WindowManager &window_manager, sf::Texture &texture);


	bool is_clicked(int pos_x, int pos_y);
	virtual void on_click() = 0;

};