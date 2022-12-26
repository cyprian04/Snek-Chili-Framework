#pragma once
#include "Board.h"
#include <assert.h>

class Snake {

private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);	 // okej czaje, proste //
		void InitBody();						 // okej czaje, proste //
		void Follow(const Segment& next);		 // okej czaje, nadaje wsp�rz�dne segmentu wcze�niejszego segmnetowi p�niejszemu, czyli np. na wcze�niejsze miejsce segments[2] wejdzie segments[2] //
		void MoveBy(const Location& delta_loc);  // okej czaje, sprawdza poprawno�� i je�li wszystko ok to zmienia warto�ci po�o�enia x i y //
		void Draw(Board& in_brd) const;
		 const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};

public:
	Snake( const Location& in_loc);				// okej czaje, daje kom�rce segments[0] warto�ci po�o�enia na mapie dla funkcji InitHead //
	void MoveBy(const Location& delta_loc);		// okej czaje, dokonuje iteracji dla ka�dego segmentu( wywo�ujemy funkcje Follow ) opr�cz g�owy, g�owa dostaje warto�� delta_loc i wywo�ujemy funkcje MoveBy dla segmentu //
	Location GetNextHeadLocation(const Location& delta_loc) const;	 	
	void Grow();								// okej czaje, odpowiada za zwi�kszenie si� ilo�ci segment�w //
	void Draw(Board& in_brd) const;				// okej czaje, odpowiada za rysowanie ca�ego Snake'a //
	bool IsInTile(const Location& target) const;
	bool IsInTileExceptEnd(const Location& target) const;

private:
	static constexpr Color headColor = Colors::Magenta;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};