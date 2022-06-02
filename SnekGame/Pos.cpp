#include "Pos.h"

Pos::Pos()
{
	this->x = 0;
	this->y = 0;
}

Pos::Pos(int x, int y)
{
	this->x = x;
	this->y = y;
}


bool operator==(const Pos& lhs, const Pos& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

Pos operator-(const Pos& lhs, const Pos& rhs)
{
	return Pos(lhs.x - rhs.x, lhs.y - rhs.y);
}

Pos operator+(const Pos& lhs, const Pos& rhs)
{
	return Pos(lhs.x + rhs.x, lhs.y + rhs.y);
}