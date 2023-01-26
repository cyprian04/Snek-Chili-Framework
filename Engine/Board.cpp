#pragma once
#include "Board.h"
#include "Snake.h"
#include <assert.h>

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

int Board::GetContent(const Location& in_loc) const
{
	return contents[in_loc.x + in_loc.y * width ];
}

void Board::SpawnContent(std::mt19937& rng, const Snake& snake, int content)
{
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || GetContent(newLoc) != 0);

	contents[newLoc.x + newLoc.y * width] = content;
}

void Board::ConsumeContent(const Location& in_loc)
{
	assert(GetContent(in_loc) == 2 || GetContent(in_loc) == 3);
	contents[in_loc.x + in_loc.y * width] = 0;
}

void Board::DrawContent()
{
	for (int y = 0; y < height ; y++)
	{
		for (int x = 0; x < width; x++)
		{
			const int contents = GetContent({ x,y });
			if (contents == 1) // obstacle
			{
				DrawCell({x,y}, Colors::Gray);
			}
			else if (contents == 2) // goal
			{
				DrawCell({ x,y }, Colors::Red);
			}
			else if (contents == 3) //poison
			{
				DrawCell({ x,y }, Colors::Cyan);
			}
		}
	}
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}
