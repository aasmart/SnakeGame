#pragma once
#include "GameObject.h"
#include "Snake.h"
#include <random>
#include <iostream>

class Game {
	const int m_width;
	const int m_height;
	GameObject** board{};
	Snake snake;
	std::array<int, 2> applePos;

	std::string m_horizontalBorders;

	const float discountFactor = 1.0f;
	const float alpha = 0.6f;
	float epsilon = 0.1f;

	std::mt19937 rng;
	std::uniform_int_distribution<std::mt19937::result_type> xDist;
	std::uniform_int_distribution<std::mt19937::result_type> yDist;
public:
	bool isActive{ true };

	/// <summary>
	/// Creates a Game object
	/// </summary>
	/// <param name="width">The width of the board</param>
	/// <param name="height">The height of the board</param>
	Game(int width, int height, std::mt19937 rng);

	~Game();

	/// <summary>
	/// Gets the board in character form
	/// </summary>
	/// <returns>The string of the board</returns>
	std::string getRenderedBoard();

	/// <summary>
	/// Gets the board's snake
	/// </summary>
	/// <returns>The Snake object</returns>
	Snake& getSnake();

	/// <summary>
	/// The core function for updating the snake's position
	/// </summary>
	void update();

	/// <summary>
	/// Creates an apple within the bounds of the game's field
	/// </summary>
	void generateApple();

	std::array<float, 3>& qFunction(std::array<int, 12> state);

	std::array<float, 3> epsilonGreedy(float epsilon, std::array<int, 12> state);

	std::array<int, 12> getState();

};