#pragma once

#include <thread>
#include <vector>
#include <memory>

#include "Village.hpp"
#include "WindowManager.hpp"

class GameManager {

private:
	bool m_running;
	std::vector<std::shared_ptr<std::thread>> m_all_threads;

	WindowManager m_window_manager;
	Village m_village;

	std::shared_ptr<VillageScene> m_village_scene;
	std::shared_ptr<BattleScene> m_battle_scene;
	std::shared_ptr<Scene> m_current_scene;


	void main_loop();

public:
	GameManager();

	void start();
	bool is_running();
	void stop();


	void swap_to_village_scene();
	void swap_to_battle_scene();

	std::shared_ptr<Scene> get_current_scene();
	std::shared_ptr<VillageScene> get_village_scene();


	Village& get_village();
	WindowManager &get_window_manager();
	void start_battle();
	void stop_battle();

	void add_thread(std::shared_ptr<std::thread> thread);

	template <typename T>
	void create_building(T* = NULL) {
		std::shared_ptr<T> building = std::make_shared<T>(m_village, *this);
		m_village.add_building(building);
	}
};