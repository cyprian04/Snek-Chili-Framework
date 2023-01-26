#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>
#include <random>

class Board
{
public:
	Board(Graphics& gfx); // konstruktor przypisuje wartoœci referencji z Graphics do nowo utworzonego elemetu gfx przez liste inicjalizacyjn¹ //
	void DrawCell(const Location& in_loc, Color c);
	void DrawBoard(Color c);
	bool IsInsideBoard(const Location& in_loc) const;
	int GetContent(const Location& in_loc) const;
	void SpawnContent( std::mt19937& rng, const class Snake& snake, int content);
	void ConsumeContent(const Location& in_loc);
	void DrawContent();

	int GetWidth() const;
	int GetHeight() const;
private:
	static constexpr int left = 100;		// jest to punkt dla wyznaczanie miejsca pêtli for do rysowania(mo¿e byæ do x i do y)
	static constexpr int def = 90;
	static constexpr int dimension = 20 ;
	static constexpr int width = 30 -2*(left - def)/ dimension;
	static constexpr int height = 20 - 2 * (left - def) / dimension;
	int contents[width * height] = { 0 }; // 0 = puste; 1 = obstacle; 2 = goal; 3 = poison 
	Graphics& gfx; /* stworzy³em obiekt typu referencji z klasy Graphcis(tak to przypadek ¿e nazwa³em go gfx)
				    aby nie musieæ dawaæ referencji z parametrem w deklaracjach funkcj tej klasy np. void DrawCell*/ 
};

