#pragma once
#include <vector>
#include <array>

enum class Direction {
	STRAIGHT,
	RIGHT,
	LEFT,
};

class Snake {
	std::array<int, 4> m_direction = {1, 0, 0 ,0};

	const int m_resetAfterMoves = 25;
public:
	int m_length{ 0 };
	// X, Y
	std::vector<std::array<int, 2>> m_snakePos;
	int m_moves = 0;

	// "Rewards"
	const int deathReward{ -150 };
	const int towardsReward{ 10 };
	const int awayReward{ -15 };
	const int winRewards{ 500 };

	/// <summary>
	/// Moves the snake in the chosen direction
	/// </summary>
	/// <returns>If the snake could successfully move</returns>
	std::tuple<bool, int> move(std::array<int, 2> applePos);

	/// <summary>
	/// Set the snake's direction and check if it is not just inversing the direction
	/// (i.e going up to down)
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	void setDirection(Direction movement);

	/// <summary>
	/// Detect if the snake's head is at the same position as the apple
	/// </summary>
	/// <param name="pos">The apple's position</param>
	/// <returns>True if the snake is colliding with the apple</returns>
	bool checkAppleCollision(std::array<int, 2> pos);

	/// <summary>
	/// Check to see if the snake collided with the boundary walls
	/// </summary>
	/// <param name="width">The width of the game board</param>
	/// <param name="height">The height of the game board</param>
	/// <returns>True if a collision was detected</returns>
	bool checkBoundaryCollision(int width, int height);

	bool isWall(int width, int height, std::array<int, 2> pos);

	std::array<int, 4> getDirectionArray();
};