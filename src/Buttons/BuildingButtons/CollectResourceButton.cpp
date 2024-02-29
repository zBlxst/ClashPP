#include "Buttons/BuildingButtons/CollectResourceButton.hpp"

#include <Buildings/ResourceGenerator.hpp>
#include "GameManager.hpp"

CollectResourceButton::CollectResourceButton(ResourceGenerator &resource_generator, GameManager &game_manager, sf::Texture &texture) :
		BuildingButton(resource_generator, game_manager, texture), m_resource_generator(resource_generator) {}

void CollectResourceButton::on_click() {
	m_resource_generator.collect();
}