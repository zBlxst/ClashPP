#include "Scenes/VillageScene.hpp"
#include "GameManager.hpp"

#include "Displayable.hpp"
#include "Clickable.hpp"

#include "Buildings/Building.hpp"

#include "Buildings/GoldTank.hpp"
#include "Buildings/GoldMine.hpp"
#include "Buildings/ManaMill.hpp"
#include "Buildings/ManaTank.hpp"
#include "Buildings/TownHall.hpp"

#include "Scenes/ShopScene.hpp"

VillageScene::VillageScene(WindowManager &window_manager, GameManager &game_manager, Village &village, bool visible) : Scene(window_manager, visible), m_game_manager(game_manager), 
							m_village(village), m_shop_scene(ShopScene(window_manager, false, village)), m_selected_building_id(-1) {}

void VillageScene::load() {
	Scene::load();
	m_text_gold.setFont(m_window_manager.get_assets_manager().get_gold_and_mana_font());
	m_text_gold.setFillColor(sf::Color::White);
	m_text_gold.setCharacterSize(24);
	m_text_gold.setString("Gold : " + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_gold()));

	m_text_mana.setFont(m_window_manager.get_assets_manager().get_gold_and_mana_font());
	m_text_mana.setFillColor(sf::Color::White);
	m_text_mana.setCharacterSize(24);
	m_text_mana.setString("Mana : " + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_mana()));
	m_text_mana.move(0.0, m_text_gold.getLocalBounds().height*(3.0/2.0));
}


void VillageScene::display() {
	Scene::display();
	m_text_gold.setString("Gold : " + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_gold()) + "/" + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_gold_max()));
	m_text_mana.setString("Mana : " + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_mana()) + "/" + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_mana_max()));

	m_window_manager.get_window().draw(m_text_gold);
	m_window_manager.get_window().draw(m_text_mana);
	
}


bool VillageScene::manage_event(sf::Event event) {
	bool catched = Scene::manage_event(event);
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
			case sf::Keyboard::A: 
				m_game_manager.create_building<TownHall>();
				catched = true;
				break;
			case sf::Keyboard::B:
				m_game_manager.create_building<GoldTank>();
				catched = true;
				break;
			case sf::Keyboard::C:
				m_game_manager.create_building<GoldMine>();
				catched = true;
				break;
			case sf::Keyboard::D:
				m_game_manager.create_building<ManaMill>();
				catched = true;
				break;
			case sf::Keyboard::E:
				m_game_manager.create_building<ManaTank>();
				catched = true;
				break;
			case sf::Keyboard::R:
				m_game_manager.get_village().get_resources_manager().add_gold(10000000000000000);
				m_game_manager.get_village().get_resources_manager().add_mana(10000000000000000);
				catched = true;
				break;
			case sf::Keyboard::S:
				open_shop();
				catched = true;
				break;
			default:
				break;	
		}

	} else if (event.type == sf::Event::MouseButtonPressed) {
		switch (event.mouseButton.button) {
			case sf::Mouse::Left:
				if (!catched) {
					unselect_building();
				}
				break;
			default:
				break;

		}
	}
	return catched;
}

int VillageScene::get_selected_building_id() {
	return m_selected_building_id;
}

void VillageScene::select_building(Building &building) {
	unselect_building();
	m_selected_building_id = building.get_id();
	building.on_select();
}

void VillageScene::unselect_building() {
	std::vector<std::shared_ptr<Building>> all_buildings = m_village.get_buildings();
	for (size_t i = 0; i < all_buildings.size(); i++) {
		if (all_buildings[i]->get_id() == m_selected_building_id) {
			all_buildings[i]->on_unselect();
		}
	}
	m_selected_building_id = -1;
}

void VillageScene::open_shop() {
	m_scene_above = std::make_shared<ShopScene>(m_shop_scene);
	m_scene_above->load(this->shared_from_this());
}

Village& VillageScene::get_village() {
	return m_village;
}