#include "GameManager.hpp"

#include "Buildings/GoldTank.hpp"
#include "Buildings/GoldMine.hpp"
#include "Buildings/ManaMill.hpp"
#include "Buildings/ManaTank.hpp"
#include "Buildings/TownHall.hpp"

#include <time.h>

GameManager::GameManager() : 	m_running(false), m_all_threads(std::vector<std::shared_ptr<std::thread>>()),
							 	m_window_manager(1000, 1000, *this), m_village(Village(*this)),
							 	m_village_scene(std::make_shared<VillageScene>(m_window_manager, *this)),
								m_battle_scene(std::make_shared<BattleScene>(m_window_manager)) {}


void GameManager::start() {
	m_running = true;
	m_window_manager.start();


	swap_to_village_scene();
	m_current_scene->load();

	create_building<TownHall>();
	create_building<GoldTank>();
	create_building<GoldMine>();
	create_building<ManaMill>();
	create_building<ManaTank>();

	m_current_scene->update_sprites();

	main_loop();



}

void GameManager::stop() {
	m_running = false;
	for (size_t i = 0; i < m_all_threads.size(); i++) {
		std::cout << "Waiting for thread " << i << std::endl;
		if (m_all_threads[i]->joinable()) {
			m_all_threads[i]->join();
		}
		std::cout << "Joined on thread " <<  i << std::endl;
	}
	m_current_scene->unload();
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

void GameManager::start_battle() {
	m_battle_scene->load(m_village);
	m_battle_scene->start_battle();
	swap_to_battle_scene();
}

void GameManager::stop_battle() {
	m_battle_scene->stop_battle();
	swap_to_village_scene();
}

std::shared_ptr<Scene> GameManager::get_current_scene() {
	return m_current_scene;
}

std::shared_ptr<VillageScene> GameManager::get_village_scene() {
	return m_village_scene;
}

void GameManager::main_loop() {
	int count = 0;
	time_t base = time(NULL);
	while (m_running) {
		m_window_manager.manage_events();
		m_window_manager.display();
		count += 1;
		//printf("Elapsed = %ld\n", time(NULL) - base);
		if (time(NULL) - base >= 1) {
			printf("\rFPS : %d", count);
			fflush(stdout);
			base = time(NULL);
			count = 0;
		}
		//printf("\rFPS : %d, %d", end, beg);

	}
}

void GameManager::swap_to_village_scene() {
	m_current_scene = m_village_scene; 
}

void GameManager::swap_to_battle_scene() {
	m_current_scene = m_battle_scene; 
}
