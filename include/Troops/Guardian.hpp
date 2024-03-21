#pragma once

#include "Troops/Troop.hpp"


class GameManager;
class Army;

class Guardian : public Troop {

private:


public:
	Guardian(GameManager &game_manager, std::shared_ptr<Army> army, std::shared_ptr<Army> opponents);


};