#include "ResourcesManager.hpp"

#include "Village.hpp"
#include "Buildings/Building.hpp"

#include <memory>
#include <iostream>
#include <string>

ResourcesManager::ResourcesManager(Village &village) : m_village(village), m_gold(0), m_mana(0), m_gold_max(0), m_mana_max(0) {}

void ResourcesManager::update_max_resources() {
	float gold_max = 0;
	float mana_max = 0;

	std::vector<std::shared_ptr<Building>> buildings = m_village.get_buildings();
	for (size_t i = 0; i < buildings.size(); i++) {
		gold_max += buildings[i]->get_gold_tank_capacity(); 
		mana_max += buildings[i]->get_mana_tank_capacity();
	}
	m_gold_max = gold_max;
	m_mana_max = mana_max;
}

float ResourcesManager::get_gold()  {
	return m_gold;
}

float ResourcesManager::get_mana()  {
	return m_mana;
}

float ResourcesManager::get_gold_max()  {
	return m_gold_max;
}

float ResourcesManager::get_mana_max()  {
	return m_mana_max;
}

void ResourcesManager::add_gold(float amount) {
	m_gold = std::max(0.0f, std::min(m_gold + amount, m_gold_max));
}

void ResourcesManager::add_mana(float amount) {
	m_mana = std::max(0.0f, std::min(m_mana + amount, m_mana_max));
}

Village& ResourcesManager::get_village()  {
	return m_village;
}

void ResourcesManager::print_resources()  {
	std::cout << "Gold : " << (long)m_gold << "/" << (long)m_gold_max << std::endl;
	std::cout << "Mana : " << (long)m_mana << "/" << (long)m_mana_max << std::endl;
}