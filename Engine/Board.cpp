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


void Board::Food::Respawn(std::mt19937& rng, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);
	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.InSideSnake(newLoc));

	loc = newLoc;
}

void Board::Food::Draw() const
{
	brd.DrawCell(loc, c);
}

const Location& Board::Food::GetLoaction() const
{
	return loc;
}
