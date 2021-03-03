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
	brd( gfx),
	snek( { 10, 4 }),
	rng(std::random_device () () ),
	nPoison(set.GetnPoison()),
	nFood(set.GetnFood()),
	ObstacleSpawnRate(set.GetObstacleSpawnRate()),
	SnakeSpeedUp(set.GetSnakeSpeedUp())
	
{
	for (int i = 0; i < nFood; i++)
	{
		brd.SpawnContent(rng, snek, Board::TileStatus::Food);
	}
	for (int i = 0; i < nPoison; i++)
	{
		brd.SpawnContent(rng, snek, Board::TileStatus::Poison);
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
	
	if (!GameOver)
	{
		snek.Movement(delta_loc, wnd.kbd);
		++SnakeMoveCounter;
		if (SnakeMoveCounter >= SnakeMoveRate)
		{
			SnakeMoveCounter = 0.0f;
			
			Location next = snek.GetNextHeadLoc(delta_loc);
			if (!brd.InSideBoard(next) || snek.InSideSnake(next) || brd.GetContent(next) == Board::TileStatus::Obstacle)
			{
				GameOver = true;
			}
			else
			{
				if (brd.GetContent(next) == Board::TileStatus::Food)
				{
					snek.Grow();
				}
				snek.SMoveBy(delta_loc);
				if (brd.GetContent(next) == Board::TileStatus::Food)
				{
					brd.ResetStatus(next);
					brd.SpawnContent(rng, snek, Board::TileStatus::Food);
					ObstacleCounter++;
					
					if (ObstacleCounter == ObstacleSpawnRate)
					{
						brd.SpawnContent(rng, snek, Board::TileStatus::Obstacle);
						ObstacleCounter = 0;
					}
				}
				if (brd.GetContent(next) == Board::TileStatus::Poison)
				{
					if (SnakeMoveRate >= 3.0f)
					{
						SnakeMoveRate -= SnakeSpeedUp;
					}
				}
			}
		}
	}
	
}

void Game::ComposeFrame()
{
	brd.DrawBorder();
	snek.Draw(brd);
	brd.DrawContent();
	if (GameOver)
	{
		SpriteCodex::DrawGameOver(350, 300, gfx);
	}

}
