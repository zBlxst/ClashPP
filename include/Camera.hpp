#pragma once

class Camera {

private:
	int m_x;
	int m_y;

public:
	Camera(int x, int y);
	int get_x();
	int get_y();
	void move(int x, int y);
	void move_rel(int x, int y);


};