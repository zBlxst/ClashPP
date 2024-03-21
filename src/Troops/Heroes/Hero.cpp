#include "Troops/Heroes/Hero.hpp"

#include "WindowManager.hpp"

Hero::Hero(GameManager &game_manager, sf::Texture &texture, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents, int max_hp, int attack, int attack_speed, int range, int move_speed, int size_in_blocks, int attack_growth, int max_hp_growth) :
	Troop(game_manager, texture, army,opponents, max_hp, attack, attack_speed, range, move_speed, false, size_in_blocks), m_level(1), m_energy(0), m_base_attack(attack), m_base_max_hp(max_hp), m_attack_growth(attack_growth), m_max_hp_growth(max_hp_growth) {}

	
void Hero::attack(std::shared_ptr<Troop> target) {
	Troop::attack(target);
	m_energy = std::min(m_energy+20, 100);
	if (m_energy >= 100) {
		m_energy = 0;
		cast_ability();
	}
}

void Hero::start() {
	update_stats();
	Troop::start();
	m_energy = 0;
}

bool Hero::is_hero() {
	return true;
}

void Hero::update_stats() {
	m_attack = m_base_attack + m_level * m_attack_growth;
	m_max_hp = m_base_max_hp + m_level * m_max_hp_growth;

}

void Hero::display() {
	Troop::display();
	if (m_visible) {
		int width = get_width();
		int height = m_window_manager.get_height_block() / 3;

		int pos_x = get_x() - m_window_manager.get_camera().get_x();
		int pos_y = get_y() - m_window_manager.get_camera().get_y() - 2*height;


		sf::RectangleShape backgroundRectangle;
		backgroundRectangle.setPosition(sf::Vector2f(pos_x, pos_y));
		backgroundRectangle.setSize(sf::Vector2f(width, height));
		backgroundRectangle.setFillColor(sf::Color(100, 100, 100));
		m_window_manager.get_window().draw(backgroundRectangle);

		sf::RectangleShape energyRectangle;
		energyRectangle.setPosition(sf::Vector2f(pos_x, pos_y));
		energyRectangle.setSize(sf::Vector2f((int)((float)width * ((float)m_energy / (float)100)), height));
		energyRectangle.setFillColor(sf::Color(0, 0, 255));
		m_window_manager.get_window().draw(energyRectangle);

	}
}