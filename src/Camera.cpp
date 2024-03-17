#include "Camera.hpp"

Camera::Camera(int x, int y) : m_x(x), m_y(y) {}

int Camera::get_x() {
	return m_x;
}

int Camera::get_y() {
	return m_y;
}

void Camera::move(int x, int y) {
	m_x = x;
	m_y = y;
}

void Camera::move_rel(int x, int y) {
	m_x += x;
	m_y += y;
}