#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>

class Board
{
public:
	Board(Graphics& gfx); // konstruktor przypisuje warto�ci referencji z Graphics do nowo utworzonego elemetu gfx przez liste inicjalizacyjn� //
	void DrawCell(const Location& in_loc, Color c);
	void DrawBoard(Color c);
	bool IsInsideBoard(const Location& in_loc) const;
	int GetWidth() const ;
	int GetHeight() const;

private:
	int left = 80;		// jest to punkt dla wyznaczanie miejsca p�tli for do rysowania(mo�e by� do x i do y)
	static constexpr int width = 31;
	static constexpr int height = 21;
	static constexpr int dimension = 20;
	Graphics& gfx; /* stworzy�em obiekt typu referencji z klasy Graphcis(tak to przypadek �e nazwa�em go gfx)
				    aby nie musie� dawa� referencji z parametrem w deklaracjach funkcj tej klasy np. void DrawCell*/ 
};

