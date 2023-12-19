#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>


#include "Village.hpp"
#include "ResourcesManager.hpp"
#include "GameManager.hpp"

#include <Building.hpp>

int main(int argc, char *argv[]) {

	std::cout << "Running the game !" << std::endl;

	GameManager game_manager;
	game_manager.start();


	return 0;
}