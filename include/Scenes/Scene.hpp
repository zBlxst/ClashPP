#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class WindowManager;
class Displayable;
class Clickable;
class Button;
class CloseSceneButton;

class Scene {

protected:
	int m_id;

	std::shared_ptr<Scene> m_scene_above; // Linked list of scene 
	std::shared_ptr<Scene> m_scene_behind;

	int m_pos_x;
	int m_pos_y;

	int m_width;
	int m_height;

	WindowManager &m_window_manager;

	std::vector<std::shared_ptr<Button>> m_buttons;
	std::vector<std::shared_ptr<Displayable>> m_displayables;
	std::vector<std::shared_ptr<Clickable>> m_clickables;

	std::shared_ptr<CloseSceneButton> m_close_scene_button;

	bool m_visible;




public:
	static int max_id;
	Scene(WindowManager &window_manager, bool visible);

	virtual void load();
	virtual void load(std::shared_ptr<Scene> behind);
	virtual void unload();

	void render();
	virtual void display();
	virtual void display_background();
	void add_displayable(std::shared_ptr<Displayable> displayable);
	void add_clickable(std::shared_ptr<Clickable> clickable);
	void add_button(std::shared_ptr<Button> button);
	void update_sprites();
	bool is_on_top();
	bool is_on_bottom();
	void back_on_top();
	int get_id();

	virtual void set_pos_and_size(std::shared_ptr<Scene> behind) = 0;

	virtual bool manage_event(sf::Event event);
	void recv_event(sf::Event event);

	int get_width();
	int get_height();

	int get_pos_x();
	int get_pos_y();


};

inline int Scene::max_id = 0;