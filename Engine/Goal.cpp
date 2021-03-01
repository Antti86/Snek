#include "Goal.h"


Goal::Goal(std::mt19937& rng, Board& brd, const Snake& snake)
{
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937& rng, Board& brd, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);
	Location newLoc;
	
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.InSideSnake(newLoc) || brd.CheckObstacle(newLoc) || brd.CheckPoison(newLoc));
	
	brd.Status[newLoc.y * brd.GetGridWidth() + newLoc.x] = Board::TileStatus::Food;
	loc = newLoc;
}



void Goal::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

void Goal::UpdateColor()	
{
	if (ColorIncr)
	{
		c = c.GetR() + 2, c.GetG() + 1, c.GetB() + 1;

		if (c.GetR() >= 253)
		{
			ColorIncr = false;
		}
	}
	else if(!ColorIncr)
	{
		c = c.GetR() - 2, c.GetG() - 1, c.GetB() - 1;

		if (c.GetR() <= 127)
		{
			ColorIncr = true;
		}
	}
}

const Location& Goal::GetLoaction() const
{
	return loc;
}



void Goal::Obstacle::Draw(Board& brd) const
{
	for (int y = 0; y < brd.GetGridHeight(); y++)
	{
		for (int x = 0; x < brd.GetGridWidth(); x++)
		{
			if (brd.CheckObstacle({ x, y }))
			{
				brd.DrawCell({ x, y }, obsColor);
			}
		}
	}
}

void Goal::Obstacle::SpawnObstacle(std::mt19937& rng, Board& brd, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);
	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.InSideSnake(newLoc) || brd.CheckObstacle(newLoc) || brd.CheckFood(newLoc) || brd.CheckPoison(newLoc));

	brd.Status[newLoc.y * brd.GetGridWidth() + newLoc.x] = Board::TileStatus::Obstacle;
	
}

void Goal::Poison::Draw(Board& brd) const
{
	for (int y = 0; y < brd.GetGridHeight(); y++)
	{
		for (int x = 0; x < brd.GetGridWidth(); x++)
		{
			if (brd.CheckPoison({ x, y }))
			{
				brd.DrawCell({ x, y }, PoisonColor);
			}
		}
	}
}

void Goal::Poison::SpawnPoison(std::mt19937& rng, Board& brd)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);
	Location Loc;

	for (; iPoison < nPoison; iPoison++)
	{
		Loc.x = xDist(rng);
		Loc.y = yDist(rng);
		if (brd.CheckFood(Loc))
		{

		}
		else
		{
			brd.Status[Loc.y * brd.GetGridWidth() + Loc.x] = Board::TileStatus::Poison;
		}
		
	}
}
