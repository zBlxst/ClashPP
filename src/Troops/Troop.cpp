#include "Troops/Troop.hpp"

#include <cmath>
#include <chrono>
#include <thread>

#include "GameManager.hpp"
#include "Army.hpp"

Troop::Troop(GameManager &game_manager, sf::Texture &texture, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents, int max_hp, int attack, int attack_speed, int range, int move_speed, bool passive, int size_in_blocks) : 
	Displayable(game_manager.get_window_manager(), texture, true), m_game_manager(game_manager), m_army(army), m_opponents(opponents), m_alive(true), m_max_hp(max_hp), m_attack(attack),
	m_attack_speed(attack_speed), m_range(range), m_move_speed(move_speed), m_passive(passive), m_size_in_blocks(size_in_blocks) {
}

void Troop::start() {
	m_alive = true;
	m_target = nullptr;		
	m_hp = m_max_hp;
	if (not is_passive()) {
		m_live_thread = std::make_shared<std::thread>(Troop::live_thread_function, std::ref(*this));
		m_game_manager.add_thread(m_live_thread);
	}
	update_sprite();
}

void Troop::stop() {
	m_alive = false;
}

void Troop::recv_damage(int amount, std::shared_ptr<Troop> source) {
	lose_hp(amount);
}

void Troop::lose_hp(int amount) {
	m_hp -= amount;
	if (m_hp <= 0) {
		die();
	}
}

void Troop::die() {
	// printf("Dead!\n");
	m_alive = false;
}

void Troop::display() {
	if (m_alive) {
		Displayable::display();
		if (m_hp < m_max_hp) {
			int pos_x = get_x() - m_window_manager.get_camera().get_x();
			int pos_y = get_y() - m_window_manager.get_camera().get_y() - get_height() / 2;

			int width = get_width();
			int height = m_window_manager.get_height_block() / 3;

			sf::RectangleShape backgroundRectangle;
			backgroundRectangle.setPosition(sf::Vector2f(pos_x, pos_y));
			backgroundRectangle.setSize(sf::Vector2f(width, height));
			backgroundRectangle.setFillColor(sf::Color(100, 100, 100));
			m_window_manager.get_window().draw(backgroundRectangle);

			sf::RectangleShape healthRectangle;
			healthRectangle.setPosition(sf::Vector2f(pos_x, pos_y));
			healthRectangle.setSize(sf::Vector2f((int)((float)width * ((float)m_hp / (float)m_max_hp)), height));
			healthRectangle.setFillColor(sf::Color(0, 255, 0));
			m_window_manager.get_window().draw(healthRectangle);
		}
	}
}


void Troop::attack(std::shared_ptr<Troop> target) {
	target->recv_damage(m_attack, this->shared_from_this());
}

bool Troop::is_alive() {
	return m_alive;
}

bool Troop::is_in_range(std::shared_ptr<Troop> troop) {
	return distance(troop) - std::min(troop->get_width(), troop->get_height()) < m_range*m_game_manager.get_window_manager().get_width_block();
}

int Troop::distance(std::shared_ptr<Troop> troop) {
	return std::max(std::abs(troop->get_center_x() - get_center_x()),std::abs(troop->get_center_y() - get_center_y()));
}

void Troop::find_target() {
	if (m_target != nullptr && m_target->is_alive() && (is_in_range(m_target) || m_move_speed > 0)) {
		return;
	} else {
		m_target = nullptr;
		std::shared_ptr<Troop> closest;
		int min_distance = -1;
		std::vector<std::shared_ptr<Troop>> all_troops = m_opponents->get_troops();
		for (size_t i = 0; i < m_opponents->get_troops().size(); i++) {
			if (m_opponents->get_troops()[i]->is_alive() && (distance(m_opponents->get_troops()[i]) < min_distance || min_distance == -1)) {
				closest = m_opponents->get_troops()[i];
				min_distance = distance(m_opponents->get_troops()[i]);
			}
		}
		if (closest != nullptr) {
			//printf("Found new target\n");
			m_target = closest;
		} else {
			//printf("Couldn't find new target\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(m_move_speed));
		}
	}
}

void Troop::attack_target() {
	if (m_target == nullptr || not m_target->is_alive() || not is_in_range(m_target) || m_attack == 0) {
		return;
	}
	attack(m_target);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Troop::move_to_target() {
	if (m_target == nullptr || not m_target->is_alive() || is_in_range(m_target) || m_move_speed == 0) {
		return;
	}
	if (m_target->get_center_x() > get_center_x()) {
		move_rel(1, 0);
	} else if (m_target->get_center_x() < get_center_x()) {
		move_rel(-1, 0);
	}

	if (m_target->get_center_y() > get_center_y()) {
		move_rel(0, 1);
	} else if (m_target->get_center_y() < get_center_y()) {
		move_rel(0, -1);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(m_move_speed));
}

void Troop::live_thread_function(Troop &troop) {
	while (troop.is_alive() and troop.get_game_manager().is_running()) {
		troop.find_target();
		troop.move_to_target();
		troop.attack_target();
	}
}

bool Troop::is_position_relative() {
	return true;
}

GameManager& Troop::get_game_manager() {
	return m_game_manager;
}

bool Troop::is_passive() {
	return m_passive;
}

void Troop::update_sprite() {
	m_size_x = m_size_in_blocks*m_game_manager.get_window_manager().get_width_block();
	m_size_y = m_size_in_blocks*m_game_manager.get_window_manager().get_height_block();
	Displayable::update_sprite();
}