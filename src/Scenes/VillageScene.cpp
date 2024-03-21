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
#include "Buttons/OpenShopButton.hpp"

VillageScene::VillageScene(WindowManager &window_manager, GameManager &game_manager) : Scene(window_manager), m_game_manager(game_manager), 
							m_shop_scene(std::make_shared<ShopScene>(window_manager, game_manager.get_village())),
							m_selected_building_id(-1), m_dragging(false), m_base_drag_x(0), m_base_drag_y(0), m_base_camera_x(0), m_base_camera_y(0), m_dragging_building(false) {

}

void VillageScene::load() {
	set_pos_and_size(m_scene_behind);
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

	if (m_open_shop_button == nullptr) {
		m_open_shop_button = std::make_shared<OpenShopButton>(m_window_manager, *this);
		add_button(m_open_shop_button);
		m_open_shop_button->load();
	}
}




void VillageScene::display() {
	Scene::display();
	m_text_gold.setString("Gold : " + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_gold()) + "/" + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_gold_max()));
	m_text_mana.setString("Mana : " + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_mana()) + "/" + std::to_string((int)m_game_manager.get_village().get_resources_manager().get_mana_max()));

	m_window_manager.get_window().draw(m_text_gold);
	m_window_manager.get_window().draw(m_text_mana);

	if (m_dragging_building) {
		sf::VertexArray line(sf::Lines, 2);
		sf::VertexArray col(sf::Lines, 2);

		for (int i = 0; i < Village::SIZE_IN_BLOCKS; i++) {
			line[0].position.x = -m_window_manager.get_camera().get_x();
			line[0].position.y =  i * m_window_manager.get_height_block() -m_window_manager.get_camera().get_y();
			line[1].position.x = (Village::SIZE_IN_BLOCKS - 1) * m_window_manager.get_width_block() -m_window_manager.get_camera().get_x();
			line[1].position.y =  i * m_window_manager.get_height_block() -m_window_manager.get_camera().get_y();
			
			col[0].position.x =  i * m_window_manager.get_width_block() -m_window_manager.get_camera().get_x();
			col[0].position.y = -m_window_manager.get_camera().get_y();
			col[1].position.x =  i * m_window_manager.get_width_block() -m_window_manager.get_camera().get_x();
			col[1].position.y = (Village::SIZE_IN_BLOCKS - 1) * m_window_manager.get_height_block() - m_window_manager.get_camera().get_y();
			


			m_window_manager.get_window().draw(line);
			m_window_manager.get_window().draw(col);
			//find_building_by_id(m_selected_building_id)->display_ghost();
		}
	}

}


bool VillageScene::manage_event(sf::Event event) {
	bool catched = Scene::manage_event(event);
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {			
			case sf::Keyboard::R:
				m_game_manager.get_village().get_resources_manager().add_gold(10000000000000000);
				m_game_manager.get_village().get_resources_manager().add_mana(10000000000000000);
				catched = true;
				break;
			case sf::Keyboard::B:
				m_game_manager.start_battle();
				catched = true;
				break;
			default:
				break;	
		}

	} else if (event.type == sf::Event::MouseButtonPressed) {
		switch (event.mouseButton.button) {
			case sf::Mouse::Right:
				if (find_building_by_id(m_selected_building_id) != nullptr && find_building_by_id(m_selected_building_id)->is_clicked(event.mouseButton.x, event.mouseButton.y)) {
						m_dragging_building = true;
						find_building_by_id(m_selected_building_id)->start_moving();
						m_base_drag_x = event.mouseButton.x;
						m_base_drag_y = event.mouseButton.y;
				} else {
					m_dragging = true;
					m_base_drag_x = event.mouseButton.x;
					m_base_drag_y = event.mouseButton.y;
					m_base_camera_x = m_window_manager.get_camera().get_x();
					m_base_camera_y = m_window_manager.get_camera().get_y();
				}
				break;
			default:
				break;

		}
	} else if (event.type == sf::Event::MouseButtonReleased) {
		switch (event.mouseButton.button) {
			case sf::Mouse::Left:
				if (!catched) {
					unselect_building();
				}
				break;
			case sf::Mouse::Right:
				if (m_dragging) {
					m_dragging = false;
				}
				if (m_dragging_building) {
					m_dragging_building = false;
					find_building_by_id(m_selected_building_id)->stop_moving();
					find_building_by_id(m_selected_building_id)->lock_position();
				}
				break;
			default:
				break;

		}
	} else if (event.type == sf::Event::MouseMoved) {
		if (m_dragging) {
			m_window_manager.get_camera().move(m_base_camera_x - event.mouseMove.x + m_base_drag_x, m_base_camera_y - event.mouseMove.y + m_base_drag_y);
		}
		if (m_dragging_building) {
			std::shared_ptr<Building> building = find_building_by_id(m_selected_building_id);
			building->set_ghost_position_in_village(building->get_position_in_village_i() + (event.mouseMove.x - m_base_drag_x) / m_window_manager.get_width_block(),
													building->get_position_in_village_j() + (event.mouseMove.y - m_base_drag_y) / m_window_manager.get_height_block());

		}
	}
	return catched;
}

void VillageScene::set_pos_and_size(std::shared_ptr<Scene> behind) {
	m_pos_x = 0;
	m_pos_y = 0;
	m_width = m_window_manager.get_width();
	m_height = m_window_manager.get_height();
}

int VillageScene::get_selected_building_id() {
	return m_selected_building_id;
}

void VillageScene::select_building(Building &building) {
	unselect_building();
	m_selected_building_id = building.get_id();
	building.on_select();
}

std::shared_ptr<Building> VillageScene::find_building_by_id(int id) {
	std::vector<std::shared_ptr<Building>> all_buildings = m_game_manager.get_village().get_buildings();
	for (size_t i = 0; i < all_buildings.size(); i++) {
		if (all_buildings[i]->get_id() == id) {
			return all_buildings[i];
		}
	}
	return nullptr;
}

void VillageScene::unselect_building() {
	if (find_building_by_id(m_selected_building_id) != nullptr) {
		find_building_by_id(m_selected_building_id)->on_unselect();
	}
	m_selected_building_id = -1;
}

void VillageScene::open_shop() {
	m_scene_above = m_shop_scene;
	m_scene_above->load(this->shared_from_this());
}

