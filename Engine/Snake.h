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
		void Follow(const Segment& next);		 // okej czaje, nadaje wspó³rzêdne segmentu wczeœniejszego segmnetowi póŸniejszemu, czyli np. na wczeœniejsze miejsce segments[2] wejdzie segments[2] //
		void MoveBy(const Location& delta_loc);  // okej czaje, sprawdza poprawnoœæ i jeœli wszystko ok to zmienia wartoœci po³o¿enia x i y //
		void Draw(Board& in_brd) const;
		 const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};

public:
	Snake( const Location& in_loc);				// okej czaje, daje komórce segments[0] wartoœci po³o¿enia na mapie dla funkcji InitHead //
	void MoveBy(const Location& delta_loc);		// okej czaje, dokonuje iteracji dla ka¿dego segmentu( wywo³ujemy funkcje Follow ) oprócz g³owy, g³owa dostaje wartoœæ delta_loc i wywo³ujemy funkcje MoveBy dla segmentu //
	Location GetNextHeadLocation(const Location& delta_loc) const;	 	
	void Grow();								// okej czaje, odpowiada za zwiêkszenie siê iloœci segmentów //
	void Draw(Board& in_brd) const;				// okej czaje, odpowiada za rysowanie ca³ego Snake'a //
	bool IsInTile(const Location& target) const;
	bool IsInTileExceptEnd(const Location& target) const;

private:
	static constexpr Color headColor = Colors::Magenta;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};