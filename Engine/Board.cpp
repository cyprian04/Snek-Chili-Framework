#pragma once
#include "Board.h"
#include "Snake.h"

Board::Board(Graphics& gfx)
	: 
	gfx(gfx)
//	 1.	 2.  //
// 1 to nowy obiekt, który dostaje przy jego tworzeniu wartoœci referencji parametru, który jest podpisany 2 //
{
}

void Board::DrawCell(const Location& in_loc, Color c)
{
	assert(in_loc.x >= 0);
	assert(in_loc.y >= 0);
	assert(in_loc.x < width);
	assert(in_loc.y < height);

	const int border = left + 10;
	gfx.DrawRectDim(in_loc.x * dimension + border, in_loc.y * dimension + border, dimension - 3, dimension - 3, c);
}

void Board::DrawBoard(Color c)
{
	gfx.DrawRect(left , left, Graphics::ScreenWidth - left, left + 5, c);
	gfx.DrawRect(left, left, left + 5, Graphics::ScreenHeight - left, c);
	gfx.DrawRect(left, Graphics::ScreenHeight - left - 5, Graphics::ScreenWidth - left, Graphics::ScreenHeight - left, c);
	gfx.DrawRect(Graphics::ScreenWidth - left - 5, left, Graphics::ScreenWidth - left, Graphics::ScreenHeight - left, c);
}

bool Board::IsInsideBoard(const Location& in_loc) const
{
	return in_loc.x >= 0 && in_loc.x < width &&
		   in_loc.y >= 0 && in_loc.y < height ;
}

bool Board::CheckObstacle(const Location& in_loc) const
{
	return hasObstacle[in_loc.x + in_loc.y * width ];
}

void Board::SpawnObstacle(std::mt19937& rng, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (CheckObstacle(newLoc) || CheckPoison(newLoc) || snake.IsInTile(newLoc) || CheckGoal(newLoc));

	hasObstacle[newLoc.x + newLoc.y * width] = true;
}

void Board::DrawObstacle()
{
	for (int y = 0; y < height ; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (CheckObstacle({x,y}))
			{
				DrawCell({x,y}, Colors::Gray);
			}
		}
	}
}

bool Board::CheckPoison(const Location& in_loc) const
{
	return hasPoison[in_loc.x + in_loc.y * width];
}

void Board::SpawnPoison(std::mt19937& rng, const Snake& snake)
{
	int a = 0;
	while(a < width*5)
	{
		std::uniform_int_distribution<int> xDist(0, width - 1);
		std::uniform_int_distribution<int> yDist(0, height - 1);

		Location newLoc;
		do
		{
			newLoc.x = xDist(rng);
			newLoc.y = yDist(rng);
		} while ( CheckPoison(newLoc) || snake.IsInTile(newLoc) || CheckGoal(newLoc));
		hasPoison[newLoc.x + newLoc.y * width] = true;
		a++;
	}
}

void Board::DrawPoison()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (CheckPoison({x,y}))
			{
				DrawCell({x,y}, Colors::Cyan);
			}
		}
	}
}

void Board::PoisonEaten(const Location& in_loc)
{
	hasPoison[in_loc.x + in_loc.y * width] = false;
}

bool Board::CheckGoal(const Location& in_loc) const
{
	return hasGoal[in_loc.x + in_loc.y * width];
}

void Board::SpawnGoal(std::mt19937& rng, const Snake& snake)
{
	int a = 0;
	while (a < 5)
	{
		std::uniform_int_distribution<int> xDist(0, width - 1);
		std::uniform_int_distribution<int> yDist(0, height - 1);

		Location newLoc;
		do
		{
			newLoc.x = xDist(rng);
			newLoc.y = yDist(rng);
		} while (CheckPoison(newLoc) || snake.IsInTile(newLoc) || CheckGoal(newLoc));
		hasGoal[newLoc.x + newLoc.y * width] = true;
		a++;
	}
}

void Board::DrawGoal()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (CheckGoal({ x,y }))
			{
				DrawCell({ x,y }, Colors::Red);
			}
		}
	}
}

void Board::RespawnGoal(const Location& in_loc, std::mt19937& rng, const Snake& snake)
{
	hasGoal[in_loc.x + in_loc.y * width] = false;

	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (CheckPoison(newLoc) || snake.IsInTile(newLoc) || CheckGoal(newLoc) || CheckObstacle(newLoc));
	hasGoal[newLoc.x + newLoc.y * width] = true;
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}
