#pragma once
#include "Board.h"
#include "MainWindow.h"


class Snake
{

private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody();
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
	void Movement(Location& delta_loc, MainWindow& wnd);
	bool InSideSnake(const Location& target) const;
	

private:
	static constexpr Color HeadColor = Colors::Yellow;
	static constexpr Color BodyColor = Colors::Green;
	static constexpr int nSegMax = 100;
	Segment segments[nSegMax];
	int nSeg = 1;

};