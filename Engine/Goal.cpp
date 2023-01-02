#pragma once
#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);
	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc));

	loc = newLoc;
}

void Goal::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

void Goal::SnakeSpeedIncrease()
{
	if (Speed <= 5)
	{
		snekMoveCounter = 0;
	}
	else if (Speed > 5 && Speed < 10)
	{
		snekMoveCounter = 10;
	}
	else if (Speed >= 10 && Speed < 15)
	{
		snekMoveCounter = 15;
	}
	else
	{
		snekMoveCounter = 20;
	}
}

const Location& Goal::GetLocation() const
{
	return loc;
}

int Goal::SetSpeed(int input)
{
	Speed += input;
	return Speed;
}

int Goal::GetsnekMovePeriod() const
{
	return snekMovePeriod;
}

int Goal::GetsnekMoveCounter()const
{
	return snekMoveCounter;
}

int Goal::SetsnekMoveCounter(int input)
{
	snekMoveCounter += input;
	return snekMoveCounter ;
}
