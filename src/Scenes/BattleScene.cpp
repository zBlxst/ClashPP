#include "Scenes/BattleScene.hpp"

#include "WindowManager.hpp"
#include "Troops/Troop.hpp"
#include "Army.hpp"

#include "Troops/Guardian.hpp"
#include "Troops/Hunter.hpp"

#include "Troops/Heroes/ThunderGod.hpp"
#include "Troops/Heroes/Druid.hpp"

#include "Village.hpp"
#include "Buildings/Building.hpp"
#include "GameManager.hpp"

#include <cstdlib>

BattleScene::BattleScene(WindowManager &window_manager) : Scene(window_manager), m_dragging(false) {}

void BattleScene::load() {
	m_defender = std::make_shared<Army>();
	m_attacker = std::make_shared<Army>();
	std::srand(std::time(nullptr));
	for (int i = 0; i < 1000; i++) {
		std::shared_ptr<Guardian> g = std::make_shared<Guardian>(m_window_manager.get_game_manager(), m_defender, m_attacker);
		std::shared_ptr<Hunter> h = std::make_shared<Hunter>(m_window_manager.get_game_manager(), m_defender, m_attacker);

		g->move(std::rand()%m_window_manager.get_width(), 100);
		m_defender->add_troop(g);

		h->move(std::rand()%m_window_manager.get_width(), 50);
		m_defender->add_troop(h);

	}

	for (int i = 0; i < 1000; i++) {
		std::shared_ptr<Guardian> g = std::make_shared<Guardian>(m_window_manager.get_game_manager(), m_attacker, m_defender);
		std::shared_ptr<Hunter> h = std::make_shared<Hunter>(m_window_manager.get_game_manager(), m_attacker, m_defender);
		g->move(std::rand()%m_window_manager.get_width(), 500);
		m_attacker->add_troop(g);

		h->move(std::rand()%m_window_manager.get_width(), 550);
		m_attacker->add_troop(h);
	}
}


void BattleScene::load(Village &village) {
	m_defender = std::make_shared<Army>();
	m_attacker = std::make_shared<Army>();
	std::srand(std::time(nullptr));

	std::vector<std::shared_ptr<Building>> buildings = village.get_buildings();
	for (size_t i = 0; i < buildings.size(); i++) {
		m_defender->add_troop(buildings[i]->get_troop_component(m_defender, m_attacker));
	}

	bool troops = false;

	if (troops) {
		for (int i = 0; i < 20; i++) {
			std::shared_ptr<Guardian> g = std::make_shared<Guardian>(m_window_manager.get_game_manager(), m_attacker, m_defender);
			//std::shared_ptr<Hunter> h = std::make_shared<Hunter>(m_window_manager.get_game_manager(), m_attacker, m_defender);
			g->move(std::rand()%m_window_manager.get_width(), 500);
			m_attacker->add_troop(g);

			//h->move(std::rand()%m_window_manager.get_width(), 550);
			//m_attacker->add_troop(h);
		}
	} else {
		std::shared_ptr<ThunderGod> tg = std::make_shared<ThunderGod>(m_window_manager.get_game_manager(), m_attacker, m_defender);
		tg->move(std::rand()%m_window_manager.get_width(), 500);
		m_attacker->add_troop(tg);

		std::shared_ptr<Druid> d = std::make_shared<Druid>(m_window_manager.get_game_manager(), m_attacker, m_defender);
		d->move(std::rand()%m_window_manager.get_width(), 500);
		m_attacker->add_troop(d);
	}
}

void BattleScene::start_battle() {
	for (size_t i = 0; i < m_defender->get_troops().size(); i++) {
		m_defender->get_troops()[i]->start();
	}

	for (size_t i = 0; i < m_attacker->get_troops().size(); i++) {
		m_attacker->get_troops()[i]->start();
	}
}


void BattleScene::stop_battle() {
	for (size_t i = 0; i < m_defender->get_troops().size(); i++) {
		m_defender->get_troops()[i]->stop();
	}

	for (size_t i = 0; i < m_attacker->get_troops().size(); i++) {
		m_attacker->get_troops()[i]->stop();
	}
}

void BattleScene::set_pos_and_size(std::shared_ptr<Scene> behind) {
	m_pos_x = 0;
	m_pos_y = 0;
	m_width = m_window_manager.get_width();
	m_height = m_window_manager.get_height();
}

void BattleScene::display() {
	std::vector<std::shared_ptr<Troop>> defender_troops = m_defender->get_troops();
	for (size_t i = 0; i < defender_troops.size(); i++) {
		defender_troops[i]->display();
	}

	std::vector<std::shared_ptr<Troop>> attacker_troops = m_attacker->get_troops();
	for (size_t i = 0; i < attacker_troops.size(); i++) {
		attacker_troops[i]->display();
	}
}


bool BattleScene::manage_event(sf::Event event) {
	bool catched = Scene::manage_event(event);

	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {			
			case sf::Keyboard::B:
				m_window_manager.get_game_manager().stop_battle();
				catched = true;
				break;
			default:
				break;	
		}

	} else if (event.type == sf::Event::MouseButtonPressed) {
		switch (event.mouseButton.button) {
			case sf::Mouse::Right:
				m_dragging = true;
				m_base_drag_x = event.mouseButton.x;
				m_base_drag_y = event.mouseButton.y;
				m_base_camera_x = m_window_manager.get_camera().get_x();
				m_base_camera_y = m_window_manager.get_camera().get_y();
				break;
			default:
				break;

		}
	} else if (event.type == sf::Event::MouseButtonReleased) {
		switch (event.mouseButton.button) {
			case sf::Mouse::Right:
				if (m_dragging) {
					m_dragging = false;
				}
				break;
			default:
				break;

		}
	} else if (event.type == sf::Event::MouseMoved) {
		if (m_dragging) {
			m_window_manager.get_camera().move(m_base_camera_x - event.mouseMove.x + m_base_drag_x, m_base_camera_y - event.mouseMove.y + m_base_drag_y);
		}
	}
	return catched;
}