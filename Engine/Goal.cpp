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
	if (Speed <= 5.0f)
	{
		snekMoveCounter = 0.0f;
	}
	else if (Speed > 5.0f && Speed < 10.0f)
	{
		snekMoveCounter = 10.0f;
	}
	else if (Speed >= 10.0f && Speed < 15.0f)
	{
		snekMoveCounter = 15.0f;
	}
	else
	{
		snekMoveCounter = 20.0f;
	}
}

const Location& Goal::GetLocation() const
{
	return loc;
}

float Goal::SetSpeed(float input)
{
	Speed += input;
	return Speed;
}

float Goal::GetsnekMovePeriod() const
{
	return snekMovePeriod;
}

float Goal::GetsnekMoveCounter()const
{
	return snekMoveCounter;
}

float Goal::SetsnekMoveCounter(float input)
{
	snekMoveCounter += input;
	return snekMoveCounter ;
}
