#include "Buttons/CloseSceneButton.hpp"

#include "Scenes/Scene.hpp"
#include "GameManager.hpp"

#include <iostream>

CloseSceneButton::CloseSceneButton(WindowManager &window_manager, Scene &scene) : 
	Button(window_manager, window_manager.get_assets_manager().get_close_scene_texture()), m_scene(scene) {
	update_sprite();
}

void CloseSceneButton::on_click() {
	m_scene.unload();
}

void CloseSceneButton::update_sprite() {
	m_size_x = (int)(0.1*m_window_manager.get_width());
	m_size_y = (int)(0.1*m_window_manager.get_height());
	Button::update_sprite();
} 


void CloseSceneButton::load() {
	m_position_x = m_scene.get_pos_x() + m_scene.get_width() - m_size_x;
	m_position_y = m_scene.get_pos_y();
	Button::load();
}