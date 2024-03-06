#include "Buttons/CreateBuildingButtons/CreateBuildingButton.hpp"

#include "GameManager.hpp"
#include <iostream>

CreateBuildingButton::CreateBuildingButton(GameManager &game_manager, sf::Texture &texture, Village &village, int class_id) : 
		Button(game_manager.get_window_manager(), texture), m_village(village), m_game_manager(game_manager), m_class_id(class_id) {

	m_size_x = 100;
	m_size_y = 100;
	move(100, 100);
	update_sprite();
}
