#pragma once
#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
	friend class Goal;
	enum class TileStatus
	{
		Empty,
		Food,
		Obstacle
	};

public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool InSideBoard(const Location& loc) const;
	void DrawBorder();
	bool CheckObstacle(const Location& loc) const;
	bool CheckFood(const Location& loc) const;

private:
	static constexpr int dimension = 16;		//boardin koordinaatit
	static constexpr int width = 40;
	static constexpr int height = 30;
	static constexpr int x = 40;
	static constexpr int y = 40;
	static constexpr int borderwidth = 5;
	static constexpr int borderpad = 2;
	static constexpr int segPadding = 1;
	static constexpr Color borderC = Colors::Blue;
	Graphics& gfx;
	TileStatus Status[width * height] = { TileStatus::Empty };
};