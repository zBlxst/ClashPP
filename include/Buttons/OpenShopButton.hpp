#pragma once

#include "Buttons/Button.hpp"

class VillageScene;
class WindowManager;

class OpenShopButton : public Button {

private:
	VillageScene &m_village_scene;


public:
	OpenShopButton(WindowManager &window_manager, sf::Texture texture, VillageScene &m_village_scene);

	void on_click();



};