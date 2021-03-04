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
		Segment(Color in_c);
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
	void SMoveBy(const Location& delta_loc);
	Location GetNextHeadLoc(Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	void Movement(Location& delta_loc, Keyboard& kbd);
	bool InSideSnake(const Location& target) const;
	
private:
	static constexpr Color HeadColor = Colors::Yellow;
	std::vector<Segment> VecSegments;

	static constexpr int nBcolors = 4;
	static constexpr Color BodyColors[nBcolors] = {
	{10, 100, 12},
	{10, 130, 40},
	{18, 80, 40},
	{10, 130, 40}
	};
};