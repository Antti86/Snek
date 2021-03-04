#pragma once
#include "Board.h"
#include "Keyboard.h"
#include <vector>

class Snake
{

private:
	class Segment
	{
	public:
		Segment() = default;
		Segment(const Location& in_loc);
		void InitBody(Color in_c);
		void MoveBy(const Location& delta_loc);
		void Follow(Segment& next);
		void Draw(Board& brd) const;
		const Location GetLocation() const;

	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location loc);
	void SMoveBy(Location& delta_loc);
	Location GetNextHeadLoc(Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	void Movement(Location& delta_loc, Keyboard& kbd);
	bool InSideSnake(const Location& target);
	
private:
	static constexpr Color HeadColor = Colors::Yellow;
	Segment segments;
	std::vector<Segment> VecSegments;
	int nSeg = 1;
	
};