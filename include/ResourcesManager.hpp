#pragma once

class Village;

class ResourcesManager {

private:
	Village &m_village;

	float m_gold;
	float m_mana;

	float m_gold_max;
	float m_mana_max;

public:
	explicit ResourcesManager(Village &village);
	void update_max_resources();

	float get_gold() ;
	float get_mana() ;

	float get_gold_max() ;
	float get_mana_max() ;

	void add_gold(float amount);
	void add_mana(float amount);

	Village& get_village() ;

	void print_resources() ;

};