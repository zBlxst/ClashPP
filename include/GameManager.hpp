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

	void main_loop();

public:
	GameManager();

	void start();
	bool is_running();
	void stop();

	Village& get_village();
	WindowManager &get_window_manager();

	void add_thread(std::shared_ptr<std::thread> thread);

	template <typename T>
	void create_building(T* = NULL) {
		std::shared_ptr<T> building = std::make_shared<T>(m_village, *this);
		m_village.add_building(building);
	}
};