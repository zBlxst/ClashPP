#pragma once

#include "Buttons/Button.hpp"
#include <memory>

class ShopScene;
class WindowManager;

class RightButton : public Button {

private:
	std::shared_ptr<ShopScene> m_shop_scene;


public:
	RightButton(WindowManager &window_manager, std::shared_ptr<ShopScene> shop_scene);

	void update_sprite();
	void on_click();
	void load();



};