#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class WindowManager;
class Displayable;
class Clickable;
class Button;

class Scene {

protected:
	WindowManager &m_window_manager;

	std::vector<std::shared_ptr<Displayable>> m_displayables;
	std::vector<std::shared_ptr<Clickable>> m_clickables;

	bool m_visible;




public:
	Scene(WindowManager &window_manager, bool visible);

	virtual void load() = 0;
	virtual void unload() = 0;

	virtual void display() = 0;
	void add_displayable(std::shared_ptr<Displayable> displayable);
	void add_clickable(std::shared_ptr<Clickable> clickable);
	void add_button(std::shared_ptr<Button> button);
	void update_sprites();

	virtual void manage_event(sf::Event event) = 0;


};