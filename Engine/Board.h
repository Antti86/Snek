#pragma once
#include "Graphics.h"
#include "Location.h"
#include "GameSettings.h"
#include <random>
#include <vector>

class Board
{
public:
	enum class TileStatus
	{
		Empty,
		Food,
		Obstacle,
		Poison
	};

public:
	Board(Graphics& gfx);
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;
	void DrawCell(const Location& loc, Color c);
	void DrawContent();
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool InSideBoard(const Location& loc) const;
	void DrawBorder();
	void SpawnContent(std::mt19937& rng, const class Snake& snake, TileStatus content);
	void ResetStatus(const Location& loc);
	TileStatus GetContent(const Location& loc) const;

private:
	Graphics& gfx;
	static constexpr int dimension = 16;		//boardin koordinaatit
	static constexpr int width = 40;
	static constexpr int height = 30;
	static constexpr int x = 40;
	static constexpr int y = 40;
	static constexpr int borderwidth = 5;
	static constexpr int borderpad = 2;
	static constexpr int segPadding = 1;
	static constexpr Color borderC = Colors::Blue;

	std::vector<TileStatus> Status{ width * height, TileStatus::Empty };

	static constexpr Color obsColor = Colors::Gray;
	static constexpr Color PoisonColor = Colors::Purple;
	static constexpr Color FoodColor = { 127, 0, 0 };


};