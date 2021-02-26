#pragma once
#include "Board.h"
#include "Snake.h"
#include <random>

class Goal
{
	
public:
	class Obstacle
	{
	public:
		void Draw(Board& brd) const;
		void SpawnObstacle(std::mt19937& rng, Board& brd, const Snake& snake);
	private:
		Color obsColor = Colors::Gray;
	};
public:
	Goal(std::mt19937& rng, Board& brd, const Snake& snake);
	void Respawn(std::mt19937& rng, Board& brd, const Snake& snake );
	void Draw(Board& brd) const;
	void UpdateColor();
	const Location& GetLoaction() const;

private:
	
	Color c = { 127, 0, 0 };
	bool ColorIncr = true;
	Location loc;
};