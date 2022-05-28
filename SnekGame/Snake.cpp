#include "Snake.h"
#include <tuple>

std::tuple<bool, int> Snake::move(std::array<int, 2> applePos) {
	int reward = 0;
	// Sets the position of the head based on the movement direction
	std::array<int, 2> newPos = m_snakePos.at(0);
	std::array<int, 2> previousPos = newPos;

	// Determine the distance from the apple before the reward
	int prevDistanceX = previousPos[0] - applePos[0];
	int prevDistanceY = previousPos[1] - applePos[1];
	int distSqr = (prevDistanceX * prevDistanceX) + (prevDistanceY * prevDistanceY);

	if (m_direction.at(0) == 1) {
		newPos[1] -= 1;
		m_snakePos.at(0) = newPos;
	}
	else if (m_direction.at(2) == 1) {
		newPos[1] += 1;
		m_snakePos.at(0) = newPos;
	}
	else if (m_direction.at(3) == 1) {
		newPos[0] -= 1;
		m_snakePos.at(0) = newPos;
	}
	else if (m_direction.at(1)) {
		newPos[0] += 1;
		m_snakePos.at(0) = newPos;
	}

	// If the rendered snake is shorter than its max length, increment it
	if (m_snakePos.size() < m_length) {
		m_snakePos.push_back(previousPos);
	}

	// Determine new distance to apple after movement
	int newDistanceX = newPos[0] - applePos[0];
	int newDistanceY = newPos[1] - applePos[1];
	int newDistSqr = (newDistanceX * newDistanceX) + (newDistanceY * newDistanceY);

	// Determine the reward
	if (newDistSqr > distSqr)
		reward += awayReward;
	else
		reward += towardsReward;

	// Loop through all the segments and change their position to the 
	// position of the previous segment
	for (int i{ 1 }; i < m_snakePos.size(); ++i) {
		newPos = previousPos;
		previousPos = m_snakePos.at(i);
		m_snakePos.at(i) = newPos;

		// Check if the head collides with any segment that isn't the empty segement
		if (i < m_snakePos.size() - 1 && m_snakePos.at(0) == newPos) {
			reward += deathReward;
			return std::make_tuple(false, reward);
		}
	}

	// Move the snake. If the snake has been moving for too long, reset the game
	m_moves++;
	if (m_moves > m_resetAfterMoves * (m_length - 1))
		return std::make_tuple(false, reward);

	return std::make_tuple(true, reward);;
}

void Snake::setDirection(Direction movement) {
	if (movement == Direction::STRAIGHT)
		return; 

	// Rotate the snake's movement
	for (int i{ 0 }; i < m_direction.size(); ++i) {
		if (m_direction.at(i) == 1) {
			int newPos = i;
			if (movement == Direction::LEFT)
				newPos--;
			else
				newPos++;

			newPos %= m_direction.size();
			m_direction[i] = 0;
			m_direction[newPos] = 1;
			return;
		}
	}
}

bool Snake::checkAppleCollision(std::array<int, 2> pos) {
	return m_snakePos.at(0) == pos;
}

bool Snake::checkBoundaryCollision(int width, int height) {
	auto& pos{ m_snakePos.at(0) };
	return isWall(width, height, pos);
}

bool Snake::isWall(int width, int height, std::array<int, 2> pos) {
	if (pos[0] < 0 || pos[0] >= width)
		return true;
	else if (pos[1] < 0 || pos[1] >= height)
		return true;
	return false;
}

std::array<int, 4> Snake::getDirectionArray() {
	return m_direction;
}