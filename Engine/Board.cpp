#pragma once
#include "Board.h"

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
	gfx.DrawRect(left + 5, left, Graphics::ScreenWidth - left, left + 5, c);
	gfx.DrawRect(left + 5, left, left, Graphics::ScreenHeight - left, c);
	gfx.DrawRect(left , Graphics::ScreenHeight - left - 5 , Graphics::ScreenWidth - left, Graphics::ScreenHeight - left , c);
	gfx.DrawRect(Graphics::ScreenWidth - left - 5, left, Graphics::ScreenWidth - left, Graphics::ScreenHeight - left,  c);

}

bool Board::IsInsideBoard(const Location& in_loc) const
{
	return in_loc.x >= 0 && in_loc.x < width &&
		   in_loc.y >= 0 && in_loc.y < height ;
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}
