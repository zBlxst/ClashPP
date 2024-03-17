#pragma once

#include "Scenes/Scene.hpp"
#include <vector>
#include <memory>


class WindowManager;
class Village;
class VillageScene;
class CreateBuildingButton;
class LeftButton;
class RightButton;


class ShopScene : public Scene, public std::enable_shared_from_this<ShopScene> {

private:
	Village &m_village;
	std::vector<std::shared_ptr<CreateBuildingButton>> m_create_buttons;
	std::shared_ptr<LeftButton> m_left_button;
	std::shared_ptr<RightButton> m_right_button;

	bool m_already_setup;
	int m_index;


public:
	ShopScene(WindowManager &window_manager, Village &m_village);
	void setup();
	void display_background();
	void display();
	void load(std::shared_ptr<Scene> behind);
	void load();
	void create_create_buttons(); // No typo here
	void set_pos_and_size(std::shared_ptr<Scene> behind);

	bool manage_event(sf::Event event);
	void update_menu();
	void increase_index(int amount);
	bool can_go_left();
	bool can_go_right();





};