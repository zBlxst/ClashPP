#include "Buttons/OpenShopButton.hpp"

#include "Scenes/VillageScene.hpp"
#include "GameManager.hpp"

#include <iostream>

OpenShopButton::OpenShopButton(WindowManager &window_manager, VillageScene &village_scene) : 
	Button(window_manager, window_manager.get_assets_manager().get_town_hall_texture()), m_village_scene(village_scene) {
	update_sprite();
}

void OpenShopButton::on_click() {
	m_village_scene.open_shop();
}

void OpenShopButton::update_sprite() {
	m_size_x = (int)(0.1*m_window_manager.get_width());
	m_size_y = (int)(0.1*m_window_manager.get_height());
	Button::update_sprite();
} 


void OpenShopButton::load() {
	m_position_x = m_window_manager.get_width() - (int)(3*m_size_x/2);
	m_position_y = m_window_manager.get_height() - (int)(3*m_size_y/2);
	Button::load();
}