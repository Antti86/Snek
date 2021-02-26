#pragma once
#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
	enum class TileStatus
	{
		Empty,
		Aplle,
		Obstacle
	};
private:
	class Food
	{
	public:
		void Respawn(std::mt19937& rng, const class Snake& snake);
		void Draw() const;
		const Location& GetLoaction() const;

	private:
		Color c = { 127, 0, 0 };
		bool ColorIncr = true;
		Location loc;
		Board& brd;
	};
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool InSideBoard(const Location& loc) const;
	void DrawBorder();
	

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