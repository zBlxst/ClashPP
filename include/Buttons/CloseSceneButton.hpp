#pragma once

#include "Buttons/Button.hpp"

class Scene;
class WindowManager;

class CloseSceneButton : public Button {

private:
	Scene &m_scene;


public:
	CloseSceneButton(WindowManager &window_manager, Scene &m_scene);

	void update_sprite();
	void on_click();
	void load();



};