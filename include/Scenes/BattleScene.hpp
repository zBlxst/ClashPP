#pragma once

#include "Scenes/Scene.hpp"

class WindowManager;
class Army;
class Village;


class BattleScene : public Scene {

private:
	std::shared_ptr<Army> m_defender;
	std::shared_ptr<Army> m_attacker;

	bool m_dragging;
	int m_base_drag_x;
	int m_base_drag_y;
	int m_base_camera_x;
	int m_base_camera_y;


public:
	BattleScene(WindowManager &window_manager);
	bool manage_event(sf::Event event);
	void set_pos_and_size(std::shared_ptr<Scene> behind);
	void display();
	void load();
	void load(Village &village);
	void start_battle();
	void stop_battle();


};