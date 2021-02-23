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
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	snek( { 10, 4 }),
	rng(std::random_device () () ),
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
	
	if (!GameOver)
	{
		snek.Movement(delta_loc, wnd);
		
		++SnakeMoveCounter;
		if (SnakeMoveCounter >= SnakeMoveRate)
		{
			SnakeMoveCounter = 0;

			Location next = snek.GetNextHeadLoc(delta_loc);
			if (!brd.InSideBoard(next) || snek.InSideSnake(next))
			{
				GameOver = true;
			}
			else
			{
				const bool eat = next == goal.GetLoaction();
				if (eat)
				{
					snek.Grow();
				}
				snek.SMoveBy(delta_loc);
				if (eat)
				{
					goal.Respawn(rng, brd, snek);
				}
			}
		}
	}
	
}

void Game::ComposeFrame()
{
	brd.DrawBorder();
	snek.Draw(brd);
	goal.Draw(brd);
	if (GameOver)
	{
		SpriteCodex::DrawGameOver(350, 300, gfx);
	}

}
