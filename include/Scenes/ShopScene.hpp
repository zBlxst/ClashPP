#pragma once

#include "Scenes/Scene.hpp"
#include <vector>
#include <memory>


class WindowManager;
class Village;
class VillageScene;
class CreateBuildingButton;

class ShopScene : public Scene {

private:
	Village &m_village;
	std::vector<std::shared_ptr<CreateBuildingButton>> m_create_buttons;


public:
	ShopScene(WindowManager &window_manager, bool visible, Village &m_village);
	void display_background();
	void display();
	void load();
	void create_create_buttons(); // No typo here

	bool manage_event(sf::Event event);





};