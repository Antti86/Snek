#pragma once

struct Location
{

	void Add(const Location& val) 
	{
		x += val.x;
		y += val.y;
	}
	bool operator ==(const Location& oikea) const
	{
		return x == oikea.x && y == oikea.y;
	}
	bool operator !=(const Location& oikea) const
	{
		return !(*this == oikea);
	}
	Location operator-() const
	{
		return { -x, -y };
	}
	int x;
	int y;
};