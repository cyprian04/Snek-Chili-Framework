#pragma once
#include "Snake.h"
#include "Board.h"
#include <random>

class Obstacles
{
public:
	void Draw(Board& brd) const;
	void spawnObst(std::mt19937& rng, const Board& brd, const Snake& snake);
	const Location& GetLocation() const;

private:
	Location loc;
};

