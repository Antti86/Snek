#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location loc)
{
	constexpr int nBcolors = 4;
	constexpr Color BodyColors[nBcolors] = {
	{10, 100, 12},
	{10, 130, 40},
	{18, 80, 40},
	{10, 130, 40}
	};
	
	for (Segment& i : VecSegments)
	{
		i.InitBody(BodyColors[i % nBcolors]);
	}
	segments[0] = Segment(loc);
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
	Location l(VecSegments.front(segments.GetLocation()));
	l.Add(delta_loc);
	return l;
}

void Snake::Grow()
{
	VecSegments.emplace_back(segments.InitBody(c));
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSeg; ++i)
	{
		segments[i].Draw(brd);
	}
}

void Snake::Movement(Location& delta_loc, Keyboard& kbd)
{
	if (kbd.KeyIsPressed(VK_UP))
	{
		delta_loc = { 0, -1 };
	}
	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		delta_loc = { 0, 1 };
	}
	else if (kbd.KeyIsPressed(VK_LEFT))
	{
		delta_loc = { -1, 0 };
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		delta_loc = { 1, 0 };
	}
}

bool Snake::InSideSnake(const Location& target)
{
	for (Segment& i : VecSegments)
	{
		if (i.GetLocation() == target)
			return true;
	}
	return false;
}



Snake::Segment::Segment(const Location& in_loc)
	:
	loc(in_loc)
{
	c = Snake::HeadColor;
}



void Snake::Segment::InitBody(Color in_c)
{
	c = in_c;
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
