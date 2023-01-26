#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>
#include <random>

class Board
{
public:
	enum class CellContent
	{
		Empty,
		Obstacle,
		Goal,
		Poison
	};
public:
	Board(Graphics& gfx); // konstruktor przypisuje warto�ci referencji z Graphics do nowo utworzonego elemetu gfx przez liste inicjalizacyjn� //
	void DrawCell(const Location& in_loc, Color c);
	void DrawBoard(Color c);
	bool IsInsideBoard(const Location& in_loc) const;
	CellContent GetContent(const Location& in_loc) const;
	void SpawnContent( std::mt19937& rng, const class Snake& snake, CellContent content);
	void ConsumeContent(const Location& in_loc);
	void DrawContent();

	int GetWidth() const;
	int GetHeight() const;
private:
	static constexpr int left = 100;		// jest to punkt dla wyznaczanie miejsca p�tli for do rysowania(mo�e by� do x i do y)
	static constexpr int def = 90;
	static constexpr int dimension = 20 ;
	static constexpr int width = 30 -2*(left - def)/ dimension;
	static constexpr int height = 20 - 2 * (left - def) / dimension;
	CellContent contents[width * height] = { CellContent::Empty };
	Graphics& gfx; /* stworzy�em obiekt typu referencji z klasy Graphcis(tak to przypadek �e nazwa�em go gfx)
				    aby nie musie� dawa� referencji z parametrem w deklaracjach funkcj tej klasy np. void DrawCell*/ 
};

