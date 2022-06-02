#include "State.h"

bool operator<(const State& lhs, const State& rhs)
{
	return lhs.obstacleLeft < rhs.obstacleLeft ||
		lhs.obstacleRight < rhs.obstacleRight ||
		lhs.obstacleUp < rhs.obstacleUp ||
		lhs.obstacleDown < rhs.obstacleDown ||

		lhs.directionUp < rhs.directionUp ||
		lhs.directionLeft < rhs.directionLeft ||
		lhs.directionRight < rhs.directionRight ||
		lhs.directionDown < rhs.directionDown ||

		lhs.foodLeft < rhs.foodLeft ||
		lhs.foodRight < rhs.foodRight ||
		lhs.foodUp < rhs.foodUp ||
		lhs.foodDown < rhs.foodDown;
}

bool operator>(const State& lhs, const State& rhs) {
	return lhs.obstacleLeft > rhs.obstacleLeft &&
		lhs.obstacleRight > rhs.obstacleRight &&
		lhs.obstacleUp > rhs.obstacleUp &&
		lhs.obstacleDown > rhs.obstacleDown &&

		lhs.directionUp > rhs.directionUp &&
		lhs.directionLeft > rhs.directionLeft &&
		lhs.directionRight > rhs.directionRight &&
		lhs.directionDown > rhs.directionDown &&

		lhs.foodLeft > rhs.foodLeft &&
		lhs.foodRight > rhs.foodRight &&
		lhs.foodUp > rhs.foodUp &&
		lhs.foodDown > rhs.foodDown;
}

bool operator==(const State& lhs, const State& rhs)
{
	{
		return lhs.obstacleLeft == rhs.obstacleLeft &&
			lhs.obstacleRight == rhs.obstacleRight &&
			lhs.obstacleUp == rhs.obstacleUp &&
			lhs.obstacleDown == rhs.obstacleDown &&

			lhs.directionUp == rhs.directionUp &&
			lhs.directionLeft == rhs.directionLeft &&
			lhs.directionRight == rhs.directionRight &&
			lhs.directionDown == rhs.directionDown &&

			lhs.foodLeft == rhs.foodLeft &&
			lhs.foodRight == rhs.foodRight &&
			lhs.foodUp == rhs.foodUp &&
			lhs.foodDown == rhs.foodDown;
	}
}

std::ostream& operator<<(std::ostream& out, const State& state)
{
	{
		out << state.obstacleLeft << state.obstacleRight << state.obstacleUp << state.obstacleDown
			<< state.directionLeft << state.directionRight << state.directionUp << state.directionDown
			<< state.foodLeft << state.foodRight << state.foodUp << state.foodDown;
		return out;
	}
}
