#include "Buttons/CreateBuildingButtons/CreateBuildingButton.hpp"

#include "GameManager.hpp"
#include <iostream>

CreateBuildingButton::CreateBuildingButton(GameManager &game_manager, sf::Texture &texture, Village &village, int class_id, std::array<int, TownHall::MAX_LEVEL+1> class_max_element,
	double gold_cost, double mana_cost) : 
		Button(game_manager.get_window_manager(), texture), m_village(village), m_game_manager(game_manager), m_class_id(class_id), m_class_max_element(class_max_element),
		m_gold_cost(gold_cost), m_mana_cost(mana_cost) {

	m_amount_text.setFont(m_window_manager.get_assets_manager().get_gold_and_mana_font());
	m_amount_text.setFillColor(sf::Color::Black);

	m_cost_text.setFont(m_window_manager.get_assets_manager().get_gold_and_mana_font());
	m_cost_text.setFillColor(sf::Color::Black);
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
			m_sprite.setColor(sf::Color(255, 255, 255));
			if (m_visible) {
				set_active(true);
			}
		}
	}
	Button::update_sprite();

}

void CreateBuildingButton::display() {
	Button::display();
	if (m_visible) {

		int text_size = 2*m_game_manager.get_window_manager().get_height_block();

		m_amount_text.setFont(m_window_manager.get_assets_manager().get_gold_and_mana_font());
		m_amount_text.setFillColor(sf::Color::Black);
		m_amount_text.setCharacterSize(text_size);
		m_amount_text.setString(std::to_string(m_village.count_building_class(m_class_id)) + "/" + std::to_string(m_class_max_element[m_village.get_town_hall_level()]));

		int pos_amount_x = get_x() + get_width() / 2 - m_amount_text.getGlobalBounds().width/2;
		int pos_amount_y = get_y() + get_height();
		m_amount_text.setPosition(pos_amount_x, pos_amount_y);

		m_window_manager.get_window().draw(m_amount_text);

		m_cost_text.setFont(m_window_manager.get_assets_manager().get_gold_and_mana_font());
		m_cost_text.setFillColor(sf::Color::Black);
		m_cost_text.setCharacterSize(text_size);
		if (m_gold_cost > 0) {
			m_cost_text.setString("Gold : " + std::to_string((int)m_gold_cost));
		} else if (m_mana_cost > 0){
			m_cost_text.setString("Mana : " + std::to_string((int)m_mana_cost));
		} else {
			m_cost_text.setString("");
		}

		int pos_cost_x = get_x() + get_width() / 2 - m_cost_text.getGlobalBounds().width/2;
		int pos_cost_y = get_y() + get_height() + text_size;
		m_cost_text.setPosition(pos_cost_x, pos_cost_y);

		m_window_manager.get_window().draw(m_cost_text);

	}
}