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

void Board::DrawContent()
{
	for (int y = 0; y < GetGridHeight(); y++)
	{
		for (int x = 0; x < GetGridWidth(); x++)
		{
			Location Loc = { x, y };

			switch (Status[Loc.y * GetGridWidth() + Loc.x])
			{
			case Board::TileStatus::Food:
				DrawCell(Loc, FoodColor);
				break;
			case Board::TileStatus::Obstacle:
				DrawCell(Loc, obsColor);
				break;
			case Board::TileStatus::Poison:
				DrawCell(Loc, PoisonColor);
				break;
			}
		}
	}
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

void Board::SpawnContent(std::mt19937& rng, const Snake& snake, TileStatus content)
{
	std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);
	Location newLoc;

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.InSideSnake(newLoc) || GetContent(newLoc) != TileStatus::Empty );

	if (content == TileStatus::Food)
	{
		Status[newLoc.y * GetGridWidth() + newLoc.x] = TileStatus::Food;
	}
	else if (content == TileStatus::Obstacle)
	{
		Status[newLoc.y * GetGridWidth() + newLoc.x] = TileStatus::Obstacle;
	}
	else if (content == TileStatus::Poison)
	{
		Status[newLoc.y * GetGridWidth() + newLoc.x] = TileStatus::Poison;
	}
}


void Board::ResetStatus(const Location& loc)
{
	Status[loc.y * width + loc.x] = TileStatus::Empty;
}

Board::TileStatus Board::GetContent(const Location& loc) const
{
	return Status[loc.y * width + loc.x];
}



