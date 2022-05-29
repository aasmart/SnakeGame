#pragma once
#include <ostream>

struct State {
	unsigned int obstacleLeft : 1;
	unsigned int obstacleRight : 1;
	unsigned int obstacleUp : 1;
	unsigned int obstacleDown : 1;

	unsigned int directionUp : 1;
	unsigned int directionRight : 1;
	unsigned int directionDown : 1;
	unsigned int directionLeft : 1;

	unsigned int foodLeft : 1;
	unsigned int foodRight : 1;
	unsigned int foodUp : 1;
	unsigned int foodDown : 1;

	friend bool operator<(const State& lhs, const State& rhs);

	friend bool operator>(const State& lhs, const State& rhs);

	friend bool operator==(const State& lhs, const State& rhs);

	friend std::ostream& operator<< (std::ostream& out, const State& state);
};

