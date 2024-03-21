#include "GameManager.hpp"

#include "Buildings/GoldTank.hpp"
#include "Buildings/GoldMine.hpp"
#include "Buildings/ManaMill.hpp"
#include "Buildings/ManaTank.hpp"
#include "Buildings/TownHall.hpp"
#include "Buildings/Tower.hpp"

#include <time.h>

#include <iostream>
#include <fstream>

GameManager::GameManager() : 	m_running(false), m_all_threads(std::vector<std::shared_ptr<std::thread>>()),
							 	m_window_manager(1000, 1000, *this), m_village(Village(*this)),
							 	m_village_scene(std::make_shared<VillageScene>(m_window_manager, *this)),
								m_battle_scene(std::make_shared<BattleScene>(m_window_manager)) {}


void GameManager::start() {
	m_running = true;
	m_window_manager.start();


	swap_to_village_scene();
	m_current_scene->load();

	std::string line;
	std::ifstream save_file("village.save");
	if (save_file.is_open() && std::getline(save_file, line) && line.compare("zBlxst\n")) {
		while (std::getline(save_file, line)) {
			parse_save_line(line);
		}
		save_file.close();
	} else {
		create_building<TownHall>();
		create_building<GoldTank>();
		create_building<GoldMine>();
		create_building<ManaMill>();
		create_building<ManaTank>();

	}


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
	
	std::string village_save_string = m_village.get_save_string();
	std::ofstream save_file; 
	save_file.open("village.save");
	save_file << "zBlxst" << std::endl;
	save_file << village_save_string;
	save_file << "Camera " << (int)m_window_manager.get_camera().get_x() << " " << (int)m_window_manager.get_camera().get_y() << std::endl;
	save_file.close();
	
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
	//m_battle_scene->load();
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
			printf("FPS : %d\n", count);
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

void GameManager::parse_save_line(std::string line) {
	if (not line.compare(0, 8, "Village ")) m_village.parse_save_line(line.substr(8, line.length() - 8));
	if (not line.compare(0, 7, "Camera ")) {
		int x, y;
		sscanf(line.substr(7, line.length() - 7).c_str(), "%d %d", &x, &y);
		m_window_manager.get_camera().move(x, y);
	}
}