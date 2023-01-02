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
	float GetsnekMoveCounter() const;
	float SetsnekMoveCounter(float input);
	float SetSpeed(float input);
	float GetsnekMovePeriod() const ;
	bool yes = false;
private:
	float Speed = 4.0f;
	float snekMoveCounter = 0.0f;
	static constexpr float snekMovePeriod = 30.0f;
	static constexpr Color c = Colors::Red;
	Location loc;
	

};