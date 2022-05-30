#include "Game.h"
#include "SnekGame.h"

Game::Game(int width, int height, std::mt19937 rng) : m_width{ width }, m_height{ height } {
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

	this->rng = rng;

	xDist.param(std::uniform_int_distribution<std::mt19937::result_type>::param_type(0, m_width - 1));
	yDist.param(std::uniform_int_distribution<std::mt19937::result_type>::param_type(0, m_height - 1));

	// Generate the first apple
	generateApple();
}

Game::~Game() {
	delete[] board;
}

std::string Game::getRenderedBoard() {
	// Set the apple's position just in case
	board[applePos.y][applePos.x] = SpriteType::APPLE;

	// Print header text and horizontal bar
	int length = snake.m_length - 1;
	std::string output{
		"Snek AI v0.4 | Current Length: " + std::to_string(length)
		+ " | Iteration: " + std::to_string(iterations) + " | Moves: " + std::to_string(snake.m_moves)
		+ " | Discoverd States: " + std::to_string(Q.size())
		+ " | High Score: " + std::to_string(highScore)
		+ "\n" };
	output += m_horizontalBorders + "\n";

	// Print the snake to the field
	for (int i{ 0 }; i < snake.m_snakePos.size(); ++i) {
		Pos pos = snake.m_snakePos.at(i);
		SpriteType sprite = (i == snake.m_snakePos.size() - 1 ?
			SpriteType::EMPTY_TILE : 
			(i == 0 ? SpriteType::SNAKE_HEAD : SpriteType::SNAKE_TAIL));
		board[pos.y][pos.x] = sprite;
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
	// Get the game state and greed function
	std::array<int, states> state = getState();
	std::array<float, 3> actions = epsilonGreedy(epsilon - (iterations * 0.00001f), state);

	// Determine which action to perform
	std::discrete_distribution<int> dist({actions.at(0), actions.at(1), actions.at(2)});

	// Perform the action and calculate the reward afer movement
	int action = dist(rng);
	snake.setDirection(static_cast<Direction>(action));
	std::tuple<bool, int> activeReward = snake.move(applePos);

	// Sets the board's status if the snake is moving and is not colliding with the walls
	isActive = std::get<0>(activeReward) && !snake.checkBoundaryCollision(m_width, m_height);

	int reward = std::get<1>(activeReward);
	std::array<int, states> new_state = getState();

	// Check to see if the snake collided with the apple
	if (snake.checkAppleCollision(applePos)) {
		snake.m_length++;
		reward += snake.winRewards;
		generateApple();
	}

	// Calculate the best action at the new position
	std::array<float, 3> newActions = qFunction(new_state);
	unsigned int bestIndex = std::max_element(std::begin(actions), std::end(actions)) - std::begin(actions);

	// Update weights
	float target = reward + discountFactor * qFunction(new_state)[bestIndex];
	float delta = target - qFunction(state)[action];
	qFunction(state)[action] += alpha * delta;

	system("cls");

	// Print the board if it's active
	if (isActive)
		std::cout << getRenderedBoard();
	else {
		highScore = snake.m_length > highScore ? snake.m_length : highScore;
		iterations++;
	}
}

void Game::generateApple() {
	while (true) {
		// Sets the X and Y position of the apple
		int x = xDist(rng);
		int y = yDist(rng);

		// Checks to see if the apple will spawn on top of the snake
		for (int i{ 0 }; i < snake.m_snakePos.size(); ++i) {
			auto& pos = snake.m_snakePos.at(i);
			// Regenerate the apple if it is
			if (pos.x == x && pos.y == y) {
				break;
			}
			else if (i == snake.m_snakePos.size() - 1) {
				// Set the apple's position
				applePos.x = x;
				applePos.y = y;
				return;
			}
		}
	}
}

std::array<float, 3>& Game::qFunction(std::array<int, states> &state) {
	// Check if the hashmap already has the value
	if (!Q.count(state))
		// Place a new value in the hashmap if the value is missing
		Q.insert(std::pair<std::array<int, states>, std::array<float, 3>>(state, { 0, 0, 0 }));

	// Return the value at the current state
	return Q.at(state);
}

std::array<float, 3> Game::epsilonGreedy(float epsilon, std::array<int, states> &state) {
	epsilon = epsilon < 0 ? 0 : epsilon;
	// Calculate the weight to give each action by default
	float weight = epsilon / 3.0f;
	std::array<float, 3> actionProbabilities = { weight, weight, weight };

	// Get the action weights at the current state and determine the best action
	std::array<float, 3> actions = qFunction(state);
	unsigned int bestIndex = std::max_element(std::begin(actions), std::end(actions)) - std::begin(actions);
	
	// Modify the probability at the best index 
	actionProbabilities[bestIndex] += (1.0f - epsilon);
	return actionProbabilities;
}

std::array<int, Game::states> Game::getState() {
	auto snake = &getSnake();
	std::array<int, 4> direction = snake->getDirectionArray();
	auto& snakeHead = snake->m_snakePos.at(0);

	Pos pointL = snakeHead - Pos(1, 0);
	Pos pointR = snakeHead + Pos(1, 0);
	Pos pointU = snakeHead - Pos(0, 1);
	Pos pointD = snakeHead + Pos(0, 1);
	Pos pointLU = pointL - Pos(0, 1);
	Pos pointLD = pointL + Pos(0, 1);
	Pos pointRU = pointR - Pos(0, 1);
	Pos pointRD = pointR + Pos(0, 1);

	std::array<int, states> state = {
		// Points of collisions to the Left, Right, Up, and Down
		snake->isWall(m_width, m_height, pointL) || !isTile(pointL, SpriteType::EMPTY_TILE),
		snake->isWall(m_width, m_height, pointR) || !isTile(pointR, SpriteType::EMPTY_TILE),
		snake->isWall(m_width, m_height, pointU) || !isTile(pointU, SpriteType::EMPTY_TILE),
		snake->isWall(m_width, m_height, pointD) || !!isTile(pointD, SpriteType::EMPTY_TILE),
		snake->isWall(m_width, m_height, pointLU) || !isTile(pointLU, SpriteType::EMPTY_TILE),
		snake->isWall(m_width, m_height, pointRU) || !isTile(pointRU, SpriteType::EMPTY_TILE),
		snake->isWall(m_width, m_height, pointLD) || !isTile(pointLD, SpriteType::EMPTY_TILE),
		snake->isWall(m_width, m_height, pointRD) || !isTile(pointRD, SpriteType::EMPTY_TILE),

		// Movement direction
		direction[0], // Up
		direction[1], // Right
		direction[2], // Down
		direction[3], // Left

		// Apple position
		applePos.x < snakeHead.x, // Food is to the left of the snake
		applePos.x > snakeHead.x, // Food is to the right of the snake
		applePos.y < snakeHead.y, // Food is above the snake
		applePos.y > snakeHead.y, // Food is below the snake
	};

	return state;
}

bool Game::isTile(Pos pos, SpriteType tileType) {
	return board[pos.y][pos.x].getSprite() == tileType;
}