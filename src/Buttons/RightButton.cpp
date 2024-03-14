#include "Buttons/RightButton.hpp"

#include "Scenes/VillageScene.hpp"
#include "GameManager.hpp"

#include <iostream>

RightButton::RightButton(WindowManager &window_manager, std::shared_ptr<ShopScene> shop_scene) : 
	Button(window_manager, window_manager.get_assets_manager().get_right_arrow_texture()), m_shop_scene(shop_scene) {
	update_sprite();
}

void RightButton::on_click() {
	m_shop_scene->increase_index(1);
}

void RightButton::update_sprite() {
	if (!m_shop_scene->can_go_right()) {
		set_active(false);
		set_visible(false);
	} else {
		set_active(true);
		set_visible(true);
	}
	m_size_x = (int)(0.1*m_shop_scene->get_width());
	m_size_y = (int)(0.1*m_shop_scene->get_height());
	Button::update_sprite();
} 


void RightButton::load() {
	update_sprite();
	m_position_x = m_shop_scene->get_pos_x() + m_shop_scene->get_width() - 3*m_size_x/2;
	m_position_y = m_shop_scene->get_pos_y() + m_shop_scene->get_height() - 3*m_size_y/2;
	Button::load();
}