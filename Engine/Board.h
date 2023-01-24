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

	bool CheckObstacle(const Location& in_loc) const;
	void SpawnObstacle( std::mt19937& rng, const class Snake& snake, const class Goal& goal);
	void DrawObstacle();

	bool CheckPoison(const Location& in_loc) const;
	void SpawnPoison(std::mt19937& rng, const class Snake& snake, const class Goal& goal);
	void DrawPoison();
	void PoisonEaten(const Location& in_loc);

	int GetWidth() const;
	int GetHeight() const;
private:
	static constexpr int left = 100;		// jest to punkt dla wyznaczanie miejsca pêtli for do rysowania(mo¿e byæ do x i do y)
	static constexpr int def = 90;
	static constexpr int dimension = 20 ;
	static constexpr int width = 30 -2*(left - def)/ dimension;
	static constexpr int height = 20 - 2 * (left - def) / dimension;
	bool hasObstacle[width * height] = { false }; 
	bool hasPoison[width * height] = { false };
	Graphics& gfx; /* stworzy³em obiekt typu referencji z klasy Graphcis(tak to przypadek ¿e nazwa³em go gfx)
				    aby nie musieæ dawaæ referencji z parametrem w deklaracjach funkcj tej klasy np. void DrawCell*/ 
};

