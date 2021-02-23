#pragma once
#include "Board.h"
#include "Snake.h"
#include <random>

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake );
	void Draw(Board& brd) const;
	void UpdateColor();
	const Location& GetLoaction() const;

private:
	static constexpr int dimension = 20;
	Color c = { 127, 0, 0 };
	bool ColorIncr = true;
	Location loc;
};