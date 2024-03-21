#pragma once

#include <memory>
#include <vector>

class Troop;

class Army {

private:
	std::vector<std::shared_ptr<Troop>> m_troops;


public:
	Army();
	std::vector<std::shared_ptr<Troop>>& get_troops();
	void add_troop(std::shared_ptr<Troop> troop);

};