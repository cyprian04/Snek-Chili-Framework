#pragma once
#include "Snake.h"
#include "Board.h"
#include <random>

class Goal {

public:
	Goal(std::mt19937& rng, const Board& in_brd, const Snake& snake);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Draw(Board& brd) const;
	void SnakeSpeedIncrease();
	const Location& GetLocation() const;
	int GetsnekMoveCounter() const;
	int SetsnekMoveCounter(int input);
	int SetSpeed(int input);
	int GetsnekMovePeriod() const ;

private:
	int Speed = 4;
	int snekMoveCounter = 0;
	static constexpr int snekMovePeriod = 40;
	static constexpr Color c = Colors::Red;
	Location loc;
	

};