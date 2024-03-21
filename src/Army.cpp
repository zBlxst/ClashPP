#include "Army.hpp"
#include <cstdio>


Army::Army() {}

std::vector<std::shared_ptr<Troop>>& Army::get_troops() {
	return m_troops;
}

void Army::add_troop(std::shared_ptr<Troop> troop) {
	m_troops.push_back(troop);
}
