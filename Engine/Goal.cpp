#include "Goal.h"


Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake)
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
	brd.DrawCell(ObLoc, obsColor);
}
