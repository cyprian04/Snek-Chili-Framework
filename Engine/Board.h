#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>

class Board
{
public:
	Board(Graphics& gfx); // konstruktor przypisuje warto�ci referencji z Graphics do nowo utworzonego elemetu gfx przez liste inicjalizacyjn� //
	void DrawCell(Location& loc_in, Color c);
	int GetWidth() const ;
	int GetHeight() const;

private:
	static constexpr int dimension = 20;
	static constexpr int width = 10;
	static constexpr int height = 10;
	Graphics& gfx; /* stworzy�em obiekt typu referencji z klasy Graphcis(tak to przypadek �e nazwa�em go gfx)
				    aby nie musie� dawa� referencji z parametrem w deklaracjach funkcj tej klasy np. void DrawCell*/ 
};

