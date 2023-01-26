/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	snek({2,2}),
	rng(std::random_device()()) // krótszy zapis aby nie robiæ deklaracji w Game.h //
	
{
	for (int i = 0; i <nPoison ; i++)
	{
		brd.SpawnContent(rng, snek, 3);
	}

	for (int i = 0; i < nGoal; i++)
	{
		brd.SpawnContent(rng, snek, 2);
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float dt = ft.Mark();

	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		isStarted = true;
	}

	if (!gameIsOver && isStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			delta_loc = {-1,0};
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			delta_loc = { 1,0 };
		}
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			delta_loc = { 0,-1 };
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			delta_loc = { 0,1 };
		}

		float snekModifiedSpeed = snekMovePeriod;
		if (wnd.kbd.KeyIsPressed(VK_CONTROL))
		{
			snekModifiedSpeed = std::min(snekMovePeriod, snakeMovePeriodSpeedUp);
		}

		snekMoveCounter += dt * 60.0f; // dostosowanie pracy countera do 60hz na sekunde //
		if (snekMoveCounter >= snekModifiedSpeed)
		{
			snekMoveCounter -= snekModifiedSpeed;
			Location next = snek.GetNextHeadLocation(delta_loc);
			const int content = brd.GetContent(next);

			if (!brd.IsInsideBoard(next) || snek.IsInTileExceptEnd(next) || content == 1)
			{
				gameIsOver = true;
			}

			else if (content == 2)
			{
				snek.Grow();
				snek.MoveBy(delta_loc);
				brd.ConsumeContent(next);
				brd.SpawnContent(rng, snek, 1);
				brd.SpawnContent(rng, snek, 2);
			}
			
			else if (content == 3)
			{
				snek.MoveBy(delta_loc);
				brd.ConsumeContent(next);
				snekMovePeriod = std::max(snekMovePeriod * snekMoveFactor, snakeMovePeriodMin);
			}				
  
			else 
			{
				snek.MoveBy(delta_loc);
			}
		}
	}
}

void Game::ComposeFrame()
{
	if (!isStarted)
	{	
		SpriteCodex::DrawTitle(300, 200, gfx);
	}
	if (isStarted )
	{
		snek.Draw(brd);
		brd.DrawBoard(Colors::Blue);
		brd.DrawContent();
	}
	if (gameIsOver) 
	{	
		SpriteCodex::DrawGameOver(350, 250, gfx);
	}
	
}