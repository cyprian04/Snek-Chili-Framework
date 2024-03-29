#pragma once
#include "Snake.h"

Snake::Snake(const Location& in_loc)
{
	constexpr int nSegmentsColor = 4;
	constexpr Color segmentsColor[nSegmentsColor] = 
	{
		{ 50 ,150, 10 },
		{ 100, 180, 10 },
		{ 50, 100, 10 },
		{ 100, 240, 10 }
	};
	for (int i = 0; i < nSegmentsMax; i++)
	{
		segments[i].InitBody(segmentsColor[i % nSegmentsColor]);
	}

	segments[0].InitHead(in_loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments- 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		++nSegments;
	}
}

void Snake::Draw(Board& in_brd) const
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(in_brd);
	}
}

bool Snake::IsInTile(const Location& target) const
{
	for (int i = 0; i < nSegments; i++) 
	{
		if (segments[i].GetLocation() == target) // mo�emy je przyr�wna�(warto�ci wsp�rz�dnych dw�ch obiekt�w) przez to �e zrobili�my prze�adowanie operatora == //
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < nSegments -1 ; i++) // odejmujemy 1 od nSegments aby nie liczy�o ogona(ostatniego bloku) w momencie wej�cia g�owy na jego stare miejsce, poniewa� ogon i tak przejdzie w inn� pozycj� // 
	{
		if (segments[i].GetLocation() == target) // mo�emy je przyr�wna�(warto�ci wsp�rz�dnych dw�ch obiekt�w) przez to �e zrobili�my prze�adowanie operatora == //
		{
			return true;
		}
	}
	return false;
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody( Color c_in)
{
	c = c_in;	
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& in_brd) const
{
	in_brd.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
