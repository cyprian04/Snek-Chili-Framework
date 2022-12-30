#pragma once
#include"Obstacles.h"

void Obstacles::RespawnObst(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);

	Location newLoc2;
		newLoc2.x = xDist(rng);
		newLoc2.y = yDist(rng);
		loc = newLoc2;
}


void Obstacles::Draw(Board& brd) const
{
	brd.DrawCell(loc, Colors::Gray);
}
const Location& Obstacles::GetLocation()
{
	return loc;
}

