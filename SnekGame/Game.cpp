#include "Game.h"

Game::Game(int width, int height) : m_width{ width }, m_height{ height } {
	// Generate the 2d array for the board
	board = new GameObject * [m_height];
	for (int row{ 0 }; row < m_height; ++row) {
		board[row] = new GameObject[m_width];
	}

	// Determine the size of the horizontal borders
	for (int i{ 0 }; i < m_width * 2 + 2; i++) {
		m_horizontalBorders += "-";
	}

	// Set the snake to the starting presets
	snake.m_length = 3;
	snake.m_snakePos.push_back({ width / 2, height / 2 });
	snake.m_snakePos.push_back({ 0, 0 });

	// Generate the first apple
	generateApple();
}

Game::~Game() {
	delete[] board;
}

std::string Game::getRenderedBoard() {
	// Set the apple's position just in case
	board[applePos[1]][applePos[0]] = SpriteType::APPLE;

	// Print header text and horizontal bar
	int length = snake.m_length - 1;
	std::string output{ "Snek v0.2 | Current Length: " + std::to_string(length) + "\n" };
	output += m_horizontalBorders + "\n";

	// Print the snake to the field
	for (int i{ 0 }; i < snake.m_snakePos.size(); ++i) {
		std::array<int, 2> pos = snake.m_snakePos.at(i);
		SpriteType sprite = (i == snake.m_snakePos.size() - 1 ?
			SpriteType::EMPTY_TILE : 
			(i == 0 ? SpriteType::SNAKE_HEAD : SpriteType::SNAKE_TAIL));
		board[pos[1]][pos[0]] = sprite;
	}

	// Print each cell of the field
	for (int row{ 0 }; row < m_height; ++row) {
		output += "|";
		for (int column{ 0 }; column < m_width; column++) {
			output += (board[row][column].getRenderedSprite()) + " ";
		}
		output += "|\n";
	}

	// Add the bottom border
	output += m_horizontalBorders;

	return output;
}

Snake& Game::getSnake() {
	return snake;
}

void Game::update() {
	// Sets the board's status if the snake is moving and is not colliding with the walls
	isActive = snake.move() && !snake.checkBoundaryCollision(m_width, m_height);

	// Check to see if the snake collided with the apple
	if (snake.checkAppleCollision(applePos)) {
		snake.m_length++;
		generateApple();
	}

	// Print the board if it's active
	if (isActive)
		std::cout << getRenderedBoard();
}

void Game::generateApple() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> xDist(0, m_width - 1);
	std::uniform_int_distribution<std::mt19937::result_type> yDist(0, m_height - 1);

	// Sets the X and Y position of the apple
	int x = xDist(rng);
	int y = yDist(rng);

	// Checks to see if the apple will spawn on top of the snake
	for (int i{ 0 }; i < snake.m_snakePos.size(); ++i) {
		auto &pos = snake.m_snakePos.at(i);
		// Regenerate the apple if it is
		if (pos[0] == x && pos[1] == y) {
			generateApple();
			return;
		}
	}

	// Set the apple's position
	applePos[0] = x;
	applePos[1] = y;
}