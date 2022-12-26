#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>

class Board
{
public:
	Board(Graphics& gfx); // konstruktor przypisuje warto�ci referencji z Graphics do nowo utworzonego elemetu gfx przez liste inicjalizacyjn� //
	void DrawCell(const Location& in_loc, Color c);
	bool IsInsideBoard(const Location& in_loc) const;
	int GetWidth() const ;
	int GetHeight() const;

private:
	static constexpr int dimension = 20;
	static constexpr int width = 25;
	static constexpr int height = 25;
	Graphics& gfx; /* stworzy�em obiekt typu referencji z klasy Graphcis(tak to przypadek �e nazwa�em go gfx)
				    aby nie musie� dawa� referencji z parametrem w deklaracjach funkcj tej klasy np. void DrawCell*/ 
};

