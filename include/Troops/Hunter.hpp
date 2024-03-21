#pragma once

#include "Troops/Troop.hpp"

class GameManager;
class Army;

class Hunter : public Troop {

private:


public:
	Hunter(GameManager &game_manager, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents);


};