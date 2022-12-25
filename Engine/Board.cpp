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

	gfx.DrawRectDim(in_loc.x * dimension, in_loc.y * dimension, dimension, dimension, c);
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}
