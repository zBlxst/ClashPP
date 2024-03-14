#pragma once

#include "Buttons/Button.hpp"

class VillageScene;
class WindowManager;

class OpenShopButton : public Button {

private:
	VillageScene &m_village_scene;


public:
	OpenShopButton(WindowManager &window_manager, VillageScene &village_scene);

	void update_sprite();
	void on_click();
	void load();



};