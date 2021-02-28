#include "Board.h"
#include "Snake.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c)
{
	const int off_x = x + borderwidth + borderpad;
	const int off_y = y + borderwidth + borderpad;

	gfx.DrawRectDim(loc.x * dimension + off_x + segPadding, loc.y * dimension + off_y + segPadding,
		dimension - segPadding * 2, dimension - segPadding * 2, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::InSideBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x <= width &&
		   loc.y >= 0 && loc.y <= height;
}

void Board::DrawBorder()
{
	const int left = x;
	const int top = y;
	const int right = x + (borderwidth + borderpad) * 2 + width * dimension;
	const int bottom = y + (borderwidth + borderpad) * 2 + height * dimension;

	gfx.DrawRect(left, top, right, top + borderwidth, borderC);
	//top
	gfx.DrawRect(left, top + borderwidth, left + borderwidth, bottom - borderwidth, borderC);
	//left
	gfx.DrawRect(left, bottom - borderwidth, right, bottom, borderC);
	//bottom
	gfx.DrawRect(right - borderwidth, top + borderwidth, right, bottom, borderC);
	//right
}

bool Board::CheckObstacle(const Location& loc) const
{
	return Status[loc.y * width + loc.x] == TileStatus::Obstacle;
}

bool Board::CheckFood(const Location& loc) const
{
	return Status[loc.y * width + loc.x] == TileStatus::Food;
}

void Board::ResetStatus(const Location& loc)
{
	Status[loc.y * width + loc.x] = TileStatus::Empty;
}



