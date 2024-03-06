#include "Scenes/ShopScene.hpp"

#include "WindowManager.hpp"
#include "Buttons/CreateBuildingButtons/CreateGoldTankButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateGoldMineButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateManaTankButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateManaMillButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateTownHallButton.hpp"
#include "Scenes/VillageScene.hpp"
#include <iostream>

ShopScene::ShopScene(WindowManager &window_manager, bool visible, Village &village) : Scene(window_manager, visible), m_village(village) {
	create_create_buttons();
}

void ShopScene::display() {
	display_background();
	Scene::display();
}

void ShopScene::create_create_buttons() {
	std::shared_ptr<CreateGoldTankButton> create_gold_tank_button = std::make_shared<CreateGoldTankButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_gold_tank_button);
	add_clickable(create_gold_tank_button);
	add_displayable(create_gold_tank_button);

	std::shared_ptr<CreateGoldMineButton> create_gold_mine_button = std::make_shared<CreateGoldMineButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_gold_mine_button);
	add_clickable(create_gold_mine_button);
	add_displayable(create_gold_mine_button);

	std::shared_ptr<CreateManaTankButton> create_mana_tank_button = std::make_shared<CreateManaTankButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_mana_tank_button);
	add_clickable(create_mana_tank_button);
	add_displayable(create_mana_tank_button);

	std::shared_ptr<CreateManaMillButton> create_mana_mill_button = std::make_shared<CreateManaMillButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_mana_mill_button);
	add_clickable(create_mana_mill_button);
	add_displayable(create_mana_mill_button);

	std::shared_ptr<CreateTownHallButton> create_town_hall_button = std::make_shared<CreateTownHallButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_town_hall_button);
	add_clickable(create_town_hall_button);
	add_displayable(create_town_hall_button);

}



void ShopScene::display_background() {
	int width_screen = m_window_manager.get_width();
	int height_screen = m_window_manager.get_height();

	int v_offset = width_screen / 10;
	int h_offset = height_screen / 10;

	int width_scene = 8*width_screen/10;
	int height_scene = 8*height_screen/10;

	sf::RenderWindow &window = m_window_manager.get_window();
	sf::RectangleShape background(sf::Vector2f(width_scene, height_scene));
	background.setFillColor(sf::Color(255, 255, 255));
	background.setPosition(sf::Vector2f(v_offset, h_offset));

	window.draw(background);
}

void ShopScene::load() {
	Scene::load();
	for (size_t i = 0; i < m_create_buttons.size(); i++) {
		m_create_buttons[i]->load();
	}
}



bool ShopScene::manage_event(sf::Event event) {
	bool catched = Scene::manage_event(event);
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
			case sf::Keyboard::Q:
				unload();
				catched = true;
				break;
			default:
				break;
		}
	}
	return catched;
}