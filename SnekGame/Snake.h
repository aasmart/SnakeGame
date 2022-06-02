#pragma once
#include <vector>
#include <array>
#include "Pos.h"

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
	std::vector<Pos> m_snakePos;
	int m_moves = 0;

	// "Rewards"
	const static int deathReward{ -1000 };
	const static int towardsReward{ 50 };
	const static int awayReward{ -60 };
	const static int winRewards{ 500 };

	/// <summary>
	/// Moves the snake in the chosen direction
	/// </summary>
	/// <returns>If the snake could successfully move</returns>
	std::tuple<bool, int> move(Pos &applePos);

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
	bool checkAppleCollision(Pos &pos);

	/// <summary>
	/// Check to see if the snake collided with the boundary walls
	/// </summary>
	/// <param name="width">The width of the game board</param>
	/// <param name="height">The height of the game board</param>
	/// <returns>True if a collision was detected</returns>
	bool checkBoundaryCollision(int width, int height);

	/// <summary>
	/// Checks is a position is a wall
	/// </summary>
	/// <param name="width">The width of the board</param>
	/// <param name="height">The height of the board</param>
	/// <param name="pos">The position on the board to check</param>
	/// <returns>True if the location is a wall</returns>
	bool isWall(int width, int height, Pos &pos);

	/// <summary>
	/// Gets the array that denotes the snake's direction
	/// </summary>
	/// <returns>The array that denotates the snake's direction</returns>
	std::array<int, 4> getDirectionArray();
};