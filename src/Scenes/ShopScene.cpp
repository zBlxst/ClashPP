#include "Scenes/ShopScene.hpp"

#include "WindowManager.hpp"
#include "Buttons/CreateBuildingButtons/CreateGoldTankButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateGoldMineButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateManaTankButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateManaMillButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateTownHallButton.hpp"
#include "Buttons/CloseSceneButton.hpp"

#include "Scenes/VillageScene.hpp"
#include <iostream>

ShopScene::ShopScene(WindowManager &window_manager, bool visible, Village &village) : Scene(window_manager ,visible), m_village(village) {
	create_create_buttons();
}

void ShopScene::display() {
	display_background();
	Scene::display();
}

void ShopScene::create_create_buttons() {
	std::shared_ptr<CreateGoldTankButton> create_gold_tank_button = std::make_shared<CreateGoldTankButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_gold_tank_button);
	add_button(create_gold_tank_button);

	std::shared_ptr<CreateGoldMineButton> create_gold_mine_button = std::make_shared<CreateGoldMineButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_gold_mine_button);
	add_button(create_gold_mine_button);

	std::shared_ptr<CreateManaTankButton> create_mana_tank_button = std::make_shared<CreateManaTankButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_mana_tank_button);
	add_button(create_mana_tank_button);

	std::shared_ptr<CreateManaMillButton> create_mana_mill_button = std::make_shared<CreateManaMillButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_mana_mill_button);
	add_button(create_mana_mill_button);

	std::shared_ptr<CreateTownHallButton> create_town_hall_button = std::make_shared<CreateTownHallButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_town_hall_button);
	add_button(create_town_hall_button);

}



void ShopScene::display_background() {
	//if (m_scene_behind == nullptr) return;

	sf::RenderWindow &window = m_window_manager.get_window();
	sf::RectangleShape background(sf::Vector2f(get_width(), get_height()));
	background.setFillColor(sf::Color(255, 255, 255));
	background.setPosition(sf::Vector2f(m_pos_x, m_pos_y));

	window.draw(background);
}

void ShopScene::load() {
	Scene::load();
	for (size_t i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->load();
	}

}

void ShopScene::load(std::shared_ptr<Scene> behind) {
	m_height = (int)(0.8*behind->get_height());
	m_width = (int)(0.8*behind->get_width());
	m_pos_x = behind->get_pos_x() + (behind->get_width() - get_width()) / 2;
	m_pos_y = behind->get_pos_y() + (behind->get_height() - get_height()) / 2;
	Scene::load(behind);
}



bool ShopScene::manage_event(sf::Event event) {
	bool catched = Scene::manage_event(event);
	return catched;
}