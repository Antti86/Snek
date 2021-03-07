#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location loc)
{
	VecSegments.emplace_back(loc);
}

void Snake::SMoveBy(const Location& delta_loc)
{
	
	for (size_t i = VecSegments.size() - 1; i > 0; --i)
	{
		VecSegments[i].Follow(VecSegments[static_cast<std::vector<Snake::Segment,
			std::allocator<Snake::Segment>>::size_type>(i) - 1]);
	}
	VecSegments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLoc(Location& delta_loc)
{
	Location l(VecSegments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Grow()
{
	VecSegments.emplace_back(BodyColors[VecSegments.size() % nBcolors]);
}

void Snake::Draw(Board& brd) const
{
	for (const Segment& e : VecSegments)
	{
		e.Draw(brd);
	}
}

void Snake::Movement(Location& delta_loc, Keyboard& kbd)
{
	if (kbd.KeyIsPressed(VK_UP))
	{
		const Location new_delta = { 0, -1 };
		if (delta_loc != -new_delta || VecSegments.size() <= 2)
		{
			delta_loc = new_delta;
		}
	}
	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		const Location new_delta = { 0, 1 };
		if (delta_loc != -new_delta || VecSegments.size() <= 2)
		{
			delta_loc = new_delta;
		}
	}
	else if (kbd.KeyIsPressed(VK_LEFT))
	{
		const Location new_delta = { -1, 0 };
		if (delta_loc != -new_delta || VecSegments.size() <= 2)
		{
			delta_loc = new_delta;
		}
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		const Location new_delta = { 1, 0 };
		if (delta_loc != -new_delta || VecSegments.size() <= 2)
		{
			delta_loc = new_delta;
		}
	}
}

bool Snake::InSideSnake(const Location& target) const
{
	for (int i = 0; i < VecSegments.size() - 1; i++)
	{
		if (VecSegments[i].GetLocation() == target)
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

Snake::Segment::Segment(Color in_c)
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
