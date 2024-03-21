#include "Scenes/ShopScene.hpp"

#include "WindowManager.hpp"
#include "Buttons/CreateBuildingButtons/CreateGoldTankButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateGoldMineButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateManaTankButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateManaMillButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateTowerButton.hpp"
#include "Buttons/CreateBuildingButtons/CreateTownHallButton.hpp"

#include "Buttons/LeftButton.hpp"
#include "Buttons/RightButton.hpp"

#include "Buttons/CloseSceneButton.hpp"

#include "Scenes/VillageScene.hpp"
#include <iostream>

ShopScene::ShopScene(WindowManager &window_manager, Village &village) : Scene(window_manager), m_village(village), m_already_setup(false), m_index(0) {}

void ShopScene::setup() {
	if (!m_already_setup) {
		m_already_setup = true;
		create_create_buttons();
	} 
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

	std::shared_ptr<CreateTowerButton> create_tower_button = std::make_shared<CreateTowerButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_tower_button);
	add_button(create_tower_button);

	std::shared_ptr<CreateTownHallButton> create_town_hall_button = std::make_shared<CreateTownHallButton>(m_window_manager.get_game_manager(), m_village);
	m_create_buttons.push_back(create_town_hall_button);
	add_button(create_town_hall_button);

	std::shared_ptr<ShopScene> pointer_to_this = this->shared_from_this();
	m_left_button = std::make_shared<LeftButton>(m_window_manager, pointer_to_this);
	add_button(m_left_button);

	m_right_button = std::make_shared<RightButton>(m_window_manager, pointer_to_this);
	add_button(m_right_button);



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
	for (size_t i = 0; i < m_displayables.size(); i++) {
		m_displayables[i]->update_sprite();
	}
	Scene::load();
	m_close_scene_button->load();
	m_left_button->load();
	m_right_button->load();
	update_menu();
}

void ShopScene::update_menu() {
	for (size_t i = 0; i < m_create_buttons.size(); i++) {
		int diff = m_create_buttons[i]->get_class_id() - m_index;
		if (0 <= diff && diff <= 2) {
			m_create_buttons[i]->resize(get_width() / 7, get_width() / 7);
			m_create_buttons[i]->move(get_pos_x() + m_create_buttons[i]->get_width()*(1+2*diff), get_pos_y() + get_height() / 2 - m_create_buttons[i]->get_height() / 2);
			m_create_buttons[i]->load();
		} else {
			m_create_buttons[i]->unload();
		}
	}
}

void ShopScene::increase_index(int amount) {
	m_index += amount;
	m_left_button->update_sprite();
	m_right_button->update_sprite();
	update_menu();
}

void ShopScene::set_pos_and_size(std::shared_ptr<Scene> behind) {
	m_height = (int)(0.8*behind->get_height());
	m_width = (int)(0.8*behind->get_width());
	m_pos_x = behind->get_pos_x() + (behind->get_width() - get_width()) / 2;
	m_pos_y = behind->get_pos_y() + (behind->get_height() - get_height()) / 2;
}

void ShopScene::load(std::shared_ptr<Scene> behind) {
	set_pos_and_size(behind);
	setup();
	Scene::load(behind);
}



bool ShopScene::manage_event(sf::Event event) {
	bool catched = Scene::manage_event(event);
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
			case sf::Keyboard::Left: 
				increase_index(-1);
				update_menu();
				catched = true;
				break;
			case sf::Keyboard::Right:
				increase_index(1);
				update_menu();
				catched = true;
				break;
			default:
				break;
		}
	}

	return catched;
}

bool ShopScene::can_go_left() {
	return m_index > 0;
}

bool ShopScene::can_go_right() {
	return m_index < (int)m_create_buttons.size() - 3;
}