#include "Buttons/OpenShopButton.hpp"

#include "Scenes/VillageScene.hpp"

OpenShopButton::OpenShopButton(WindowManager &window_manager, sf::Texture texture, VillageScene &village_scene) : Button(window_manager, texture), m_village_scene(village_scene) {}

void OpenShopButton::on_click() {
	m_village_scene.open_shop();
}