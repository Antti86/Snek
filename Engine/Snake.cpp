#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location loc)
{
	segments[0].InitHead(loc);
}

void Snake::SMoveBy(Location& delta_loc)
{
	for (int i = nSeg - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLoc(Location& delta_loc)
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Grow()
{
	if (nSeg < nSegMax)
	{
		segments[nSeg].InitBody();
		++nSeg;
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSeg; ++i)
	{
		segments[i].Draw(brd);
	}
}

void Snake::Movement(Location& delta_loc, MainWindow& wnd)
{
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		delta_loc = { 0, -1 };
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		delta_loc = { 0, 1 };
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		delta_loc = { -1, 0 };
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		delta_loc = { 1, 0 };
	}
}

bool Snake::InSideSnake(const Location& target) const
{
	for (int i = 0; i < nSeg - 1; ++i)
	{
		if (segments[i].GetLocation() == target)
			return true;
	}
	return false;
}



void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::HeadColor;
}

void Snake::Segment::InitBody()
{
	c = Snake::BodyColor;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert (abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Follow(Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location Snake::Segment::GetLocation() const
{
	return loc;
}
