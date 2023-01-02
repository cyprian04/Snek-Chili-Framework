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
	rng(std::random_device()()), // kr�tszy zapis aby nie robi� deklaracji w Game.h //
	goal(rng, brd, snek)
{
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

		float dt = ft.Mark();
		goal.SetsnekMoveCounter( dt * 60.0f);

		if (goal.GetsnekMoveCounter() >= goal.GetsnekMovePeriod())
		{
			goal.SnakeSpeedIncrease();

			Location next = snek.GetNextHeadLocation(delta_loc);
			
			if (!brd.IsInsideBoard(next) || snek.IsInTileExceptEnd(next) || Colliding(next))
			{
				gameIsOver = true;
			}
			else
			{
				const bool eating = next == goal.GetLocation();
				PreventCollision();
				
				if (eating)
				{
					snek.Grow();
					goal.SetSpeed(1.0f);
				}
				snek.MoveBy(delta_loc);
				if (eating)
				{	
					goal.Respawn(rng, brd, snek);
					spawn = true;
					rest = nObstacle;
					++nObstacle;
					for (int i = rest; i < nObstacle; i++)
					{
						obstacle[i].spawnObst(rng, brd, snek );
					}
				}
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
		goal.Draw(brd);
		if (spawn)
		{
			for (int i = 0; i < nObstacle; i++)
			{
				obstacle[i].Draw(brd);
			}
		}
		brd.DrawBoard(Colors::Blue);
	}
	if (gameIsOver) 
	{	
		SpriteCodex::DrawGameOver(350, 250, gfx);
	}
	
}

bool Game::Colliding(const Location& next) const
{
	for (int i = 0; i < nObstacle; i++)
	{
		if (obstacle[i].GetLocation() == next)
		return true;
	}
	return false;
}

void Game::PreventCollision()
{
	for (int i = 0; i < nObstacle; i++)
	{
		Location obst = obstacle[i].GetLocation();
		if (obst == goal.GetLocation())
			goal.Respawn(rng, brd, snek);				
	}
}
