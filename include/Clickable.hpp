#pragma once

#include "Displayable.hpp"

class Clickable : public Displayable {

protected:
	bool m_active;

public:
	Clickable(WindowManager &window_manager, sf::Texture &texture, bool active, bool visible);


	bool is_clicked(int pos_x, int pos_y);
	virtual void on_click() = 0;

	bool get_active();
	void set_active(bool value);

};