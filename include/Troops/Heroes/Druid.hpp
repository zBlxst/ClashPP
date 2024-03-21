#pragma once

#include "Troops/Heroes/Hero.hpp"

class Druid : public Hero {

public:
	Druid(GameManager &game_manager, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents);
	void cast_ability();


};