#pragma once

struct Pos {
	int x;
	int y;

	Pos();

	Pos(int x, int y);

	friend bool operator==(const Pos& lhs, const Pos& rhs);

	friend Pos operator-(const Pos& lhs, const Pos& rhs);

	friend Pos operator+(const Pos& lhs, const Pos& rhs);
};