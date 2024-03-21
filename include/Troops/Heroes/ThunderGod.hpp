#pragma once

#include "Troops/Heroes/Hero.hpp"

class ThunderGod : public Hero {

public:
	ThunderGod(GameManager &game_manager, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents);
	void cast_ability();


};