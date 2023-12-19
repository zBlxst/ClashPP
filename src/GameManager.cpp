#include "GameManager.hpp"

#include "GoldTank.hpp"
#include "GoldMine.hpp"
#include "ManaMill.hpp"
#include "ManaTank.hpp"
#include "TownHall.hpp"

GameManager::GameManager() : 	m_running(false), m_all_threads(std::vector<std::shared_ptr<std::thread>>()),
							 	m_village(Village(*this)), m_window_manager(1200, 1200, *this) {}


void GameManager::start() {
	m_running = true;
	m_window_manager.start();


	create_building<TownHall>();
	create_building<GoldTank>();
	create_building<GoldMine>();
	create_building<ManaMill>();
	create_building<ManaTank>();

	m_window_manager.update_sprites();

	main_loop();



}

void GameManager::stop() {
	m_running = false;
	std::cout << "GameManager is stoping" << std::endl;
	for (size_t i = 0; i < m_all_threads.size(); i++) {
		std::cout << "Waiting for thread " << i << std::endl;
		std::cout << "Joining on thread " <<  i << std::endl;
		m_all_threads[i]->join();
	}
	m_window_manager.stop();
}

bool GameManager::is_running() {
	return m_running;
}

void GameManager::add_thread(std::shared_ptr<std::thread> thread) {
	m_all_threads.push_back(thread);
}

Village& GameManager::get_village() {
	return m_village;
}

WindowManager &GameManager::get_window_manager() {
	return m_window_manager;
}

void GameManager::main_loop() {

	while (m_running) {
		m_window_manager.manage_events();
		m_window_manager.display();

	}
}
