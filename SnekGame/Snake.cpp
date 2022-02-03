#include "Snake.h"

bool Snake::move() {
	// Sets the position of the head based on the movement direction
	std::array<int, 2> newPos = m_snakePos.at(0);
	std::array<int, 2> previousPos = newPos;
	switch (m_moveDirection) {
	case Direction::UP:
		newPos[1] -= 1;
		m_snakePos.at(0) = newPos;
		break;
	case Direction::DOWN:
		newPos[1] += 1;
		m_snakePos.at(0) = newPos;
		break;
	case Direction::LEFT:
		newPos[0] -= 1;
		m_snakePos.at(0) = newPos;
		break;
	case Direction::RIGHT:
		newPos[0] += 1;
		m_snakePos.at(0) = newPos;
		break;
	}

	// If the rendered snake is shorter than its max length, increment it
	if (m_snakePos.size() < m_length) {
		m_snakePos.push_back(previousPos);
	}

	// Loop through all the segments and change their position to the 
	// position of the previous segment
	for (int i{ 1 }; i < m_snakePos.size(); ++i) {
		newPos = previousPos;
		previousPos = m_snakePos.at(i);
		m_snakePos.at(i) = newPos;

		// Check if the head collides with any segment that isn't the empty segement
		if (i < m_snakePos.size() - 1 && m_snakePos.at(0) == newPos)
			return false;
	}

	// Set the previous direction to the direction the snake travelled in
	m_previousDirection = m_moveDirection;
	return true;
}

void Snake::setDirection(Direction direction) {
	if (direction == Direction::UP && m_previousDirection != Direction::DOWN) {
		m_moveDirection = Direction::UP;
	}
	else if (direction == Direction::DOWN && m_previousDirection != Direction::UP) {
		m_moveDirection = Direction::DOWN;
	}
	else if (direction == Direction::LEFT && m_previousDirection != Direction::RIGHT) {
		m_moveDirection = Direction::LEFT;
	}
	else if (direction == Direction::RIGHT && m_previousDirection != Direction::LEFT) {
		m_moveDirection = Direction::RIGHT;
	}
}

bool Snake::checkAppleCollision(std::array<int, 2> pos) {
	return m_snakePos.at(0) == pos;
}

bool Snake::checkBoundaryCollision(int width, int height) {
	auto& pos{ m_snakePos.at(0) };
	if (pos[0] < 0 || pos[0] >= width)
		return true;
	else if (pos[1] < 0 || pos[1] >= height)
		return true;
	return false;
}