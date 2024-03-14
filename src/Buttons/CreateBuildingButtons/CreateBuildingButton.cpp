#include "Buttons/CreateBuildingButtons/CreateBuildingButton.hpp"

#include "GameManager.hpp"
#include <iostream>

CreateBuildingButton::CreateBuildingButton(GameManager &game_manager, sf::Texture &texture, Village &village, int class_id, std::array<int, TownHall::MAX_LEVEL+1> class_max_element,
	double gold_cost, double mana_cost) : 
		Button(game_manager.get_window_manager(), texture), m_village(village), m_game_manager(game_manager), m_class_id(class_id), m_class_max_element(class_max_element),
		m_gold_cost(gold_cost), m_mana_cost(mana_cost) {

	update_sprite();
}

int CreateBuildingButton::get_class_id() {
	return m_class_id;
}

void CreateBuildingButton::update_sprite() {
	if (m_village.count_building_class(m_class_id) >= m_class_max_element[m_village.get_town_hall_level()] or not m_village.can_afford(m_gold_cost, m_mana_cost)) {
		if (m_active) {
			m_sprite.setColor(sf::Color(100, 100, 100));
			set_active(false);
		}
	} else {
		if (not m_active) {
			printf("Here\n");
			m_sprite.setColor(sf::Color(255, 255, 255));
			set_active(true);
		}
	}
	Button::update_sprite();

}