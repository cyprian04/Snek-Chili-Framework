#pragma once
#include "Board.h"

Board::Board(Graphics& gfx)
	: 
	gfx(gfx)
//	 1.	 2.  //
// 1 to nowy obiekt, który dostaje przy jego tworzeniu wartoœci referencji parametru, który jest podpisany 2 //
{
}

void Board::DrawCell(Location& loc_in, Color c)
{
	assert(loc_in.x >= 0);
	assert(loc_in.y >= 0);
	assert(loc_in.x < width);
	assert(loc_in.y < height);

	gfx.DrawRectDim(loc_in.x * dimension, loc_in.y * dimension, dimension, dimension, c);
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}
