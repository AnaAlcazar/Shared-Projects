﻿#include "GameStateMachine.hpp"
#include "Globals.hpp"
#include "Game.hpp"
#include "Debugger.hpp"
#include <iostream>

void GameStateMachine::Start()
{
	timer = 0;
	switch (currentState)
	{
	case 0:

		highscore = FileReader::Instance().ReadHighScore();
		break;
	case 1:
		break;
	case 2:
		highscore = FileReader::Instance().ReadHighScore();
		break;
	case 3:
		game = new Game();
		game->Start(true);
		break;
	case 4:
		break;
	default:
		break;
	}
}

void GameStateMachine::Input()
{
	switch (currentState)
	{
	case 0:
		if (IsKeyPressed(KEY_TAB)) { coins++;  SetState(2); }
		break;
	case 1:
		if (IsKeyPressed(KEY_TAB)) { coins++;  SetState(2); }
		break;
	case 2:
		if (IsKeyPressed(KEY_TAB) && coins < 99)coins++;
		if (IsKeyPressed(KEY_ENTER))
		{
			AudioManager::Instance().PlayMusicByName("Start_Game");
			SetState(3);
		}
		break;
	case 3:
		game->Input();
		Debugger::Instance().Input();
		break;
	case 4:
		break;
	default:
		break;
	}
}

void GameStateMachine::Logic()
{
	switch (currentState)
	{
	case 0:
		timer += GetFrameTime();
		if (timer > 32)SetState(1);
		break;
	case 1:
		timer += GetFrameTime();
		if (timer > 16)SetState(0);
		break;
	case 2:
		break;
	case 3:
		game->Logic();
		break;
	case 4:
		break;
	default:
		break;
	}
}

void GameStateMachine::Render()
{
	switch (currentState)
	{
	case 0:
		ScreenManager::Instance().Render(0, WHITE);
		
		if (timer <= 3)
		{
			Renderer::Instance().DrawText("This game is for education", 26, { 8,8 }, WHITE);
			Renderer::Instance().DrawText("purpose created on project", 26, { 8,24 }, WHITE);
			Renderer::Instance().DrawText("1 of CITM university", 20, { 32,40 }, WHITE);
			Renderer::Instance().DrawText("No copyright intended ~", 23, { 20,272 }, WHITE);
		}
		else if (timer > 3 && timer <= 6)
		{
			Renderer::Instance().DrawSprite(3,{0,0},{144,144},WHITE);
			Renderer::Instance().DrawText("CITM - UPC", 10, { 72,24 }, WHITE);
			Renderer::Instance().DrawText("student        ana alcazar", 26, { 8,56 }, WHITE);
			Renderer::Instance().DrawText("tutor         jesus alonso", 26, { 8,72 }, WHITE);
			Renderer::Instance().DrawText("               marc torres", 26, { 8,88 }, WHITE);
		}
		else
		{
			
			Renderer::Instance().DrawText("   1UP   HIGH SCORE   2UP  ", 28, { 0,0 }, WHITE);
			Renderer::Instance().DrawText("00", 2, { 40,8 }, WHITE);
			Renderer::Instance().DrawNumber(highscore, Renderer::Instance().AnchorNumberOnRight( highscore, { 128,8 }), WHITE);
			Renderer::Instance().DrawText("  CREDIT 0", 10, { 0,280 }, WHITE);
			if (timer > 6.5f)Renderer::Instance().DrawText("       CHARACTER / NICKNAME ", 28, { 0,48 }, WHITE);
#pragma region Blinky
			if(timer > 7)Renderer::Instance().DrawSprite(0, { 0,2 }, { 40, 68 }, WHITE);
			if(timer > 7.5f)Renderer::Instance().DrawText("       -SHADOW", 14, { 0,64 }, 5);
			if(timer > 8)Renderer::Instance().DrawText("                  'BLINKY'  ", 28, { 0,64 }, 5);
#pragma endregion
#pragma region Pinky
			if (timer > 9)Renderer::Instance().DrawSprite(0, { 0,3 }, { 40, 92 }, WHITE);
			if (timer > 9.5f)Renderer::Instance().DrawText("       -SPEEDY", 14, { 0,88 }, 2);
			if (timer > 10)Renderer::Instance().DrawText("                  'PINKY'   ", 28, { 0,88 }, 2);
#pragma endregion
#pragma region Inky
			if (timer > 11)Renderer::Instance().DrawSprite(0, { 0,4 }, { 40, 116 }, WHITE);
			if (timer > 11.5f)Renderer::Instance().DrawText("       -BASHFUL", 15, { 0,112 }, 1);
			if (timer > 12)Renderer::Instance().DrawText("                  'INKY'    ", 28, { 0,112 }, 1);
#pragma endregion
#pragma region Clyde
			if (timer > 13)Renderer::Instance().DrawSprite(0, { 0,5 }, { 40, 140 }, WHITE);
			if (timer > 13.5f)Renderer::Instance().DrawText("       -POKEY", 13, { 0,136 }, 3);
			if (timer > 14)Renderer::Instance().DrawText("                  'CLYDE'    ", 28, { 0,136 }, 3);
#pragma endregion
			if (timer > 15) { 
				Renderer::Instance().DrawText("10 :", 6, { 96,200 }, WHITE); Renderer::Instance().DrawSprite(1, { 18,0 }, { 88, 204 }, 4);
				Renderer::Instance().DrawText("50 :", 6, { 96,216 }, WHITE); Renderer::Instance().DrawSprite(1, { 19,0 }, { 88, 220 }, 4);
			}
			if (timer > 16)
			{
				Renderer::Instance().DrawText("    ~ 1980 MIDWAY MFG. CO.   ", 28, { 0,248 }, 2);
				if(timer < 23.25f)
					Renderer::Instance().DrawSprite(1, { 19,0 }, { 36, 176 }, 4);
			}
			if (timer > 17)
			{
				if (timer < 23.25f)
				{
					float pacPos = 224 -(timer-17)*30;
					float bPos = 280 - (timer - 17) * 30;
					float pPos = 296 - (timer - 17) * 30;
					float iPos = 312 - (timer - 17) * 30;
					float cPos = 328 - (timer - 17) * 30;
					pellet.Animate({ 36, 176 }, 0, 0.1f, true);
					pacman.Animate({ pacPos, 176 }, 0, 0.1f, true);
					b.Animate({ bPos, 176 }, 0, 0.1f, true);
					p.Animate({ pPos, 176 }, 0, 0.1f, true);
					i.Animate({ iPos, 176 }, 0, 0.1f, true);
					c.Animate({ cPos, 176 }, 0, 0.1f, true);
				}
				else
				{
					float pacPos = 36 + (timer - 23.25f) * 30;
					float bPos = 92 + 3 * 12;
					float pPos = 108 + 4 * 12;
					float iPos = 124 + 5 * 12;
					float cPos = 140 + 6 * 12;
					if (timer < 26.25f)
					{
						bPos = 92 + (timer - 23.25f) * 12;
						b.Animate({ bPos, 176 }, 1, 0.1f, true);
					}
					if (timer > 26.25f && timer < 26.75f)
						Renderer::Instance().DrawSprite(0, { 10,1 }, { bPos, 176 }, WHITE);
					if (timer < 27.2f)
					{
						pPos = 108 + (timer - 23.25f) * 12;
						p.Animate({ pPos, 176 }, 1, 0.1f, true);
					}
						if (timer > 27.2f && timer < 27.7f)
						Renderer::Instance().DrawSprite(0, { 12,0 }, { pPos, 176 }, WHITE);
					if (timer < 28.15f)
					{
						iPos = 124 + (timer - 23.25f) * 12;
						i.Animate({ iPos, 176 }, 1, 0.1f, true);
					}
						if (timer > 28.15f && timer < 28.65f)
						Renderer::Instance().DrawSprite(0, { 13,1 }, { iPos, 176 }, WHITE);
					if (timer < 29.1f)
					{
						cPos = 140 + (timer - 23.25f) * 12;
						c.Animate({ cPos, 176 }, 1, 0.1f, true);
					}
					if (timer > 29.1f && timer < 29.6f)
					{
						Renderer::Instance().DrawSprite(0, { 13,3 }, { cPos, 176 }, WHITE);
						Renderer::Instance().DrawSprite(0, { 12,3 }, { cPos - 16, 176 }, WHITE);
					}
						
					pacman.Animate({ pacPos, 176 }, 1, 0.1f, true);
				}
			}
		}
		break;
	case 1:
		ScreenManager::Instance().Render(0, 0);
		Renderer::Instance().DrawText("          CONTROLS          ", 28, { 0,8 }, WHITE);
		timer += GetFrameTime();
		if (timer > 0 && timer < 2 || timer > 8 && timer < 10)
		{
			pacman.Animate({ 104,136 }, 0, 0.1f, true);
			Renderer::Instance().DrawText("          A    LEFT ARROW   ", 28, { 0,160 }, WHITE);
		}
		else if (timer > 2 && timer < 4 || timer > 10 && timer < 12)
		{
			pacman.Animate({ 104,136 }, 2, 0.1f, true);
			Renderer::Instance().DrawText("          W    UP ARROW     ", 28, { 0,160 }, WHITE);
		}
		else if (timer > 4 && timer < 6 || timer > 12 && timer < 14)
		{
			pacman.Animate({ 104,136 }, 1, 0.1f, true);
			Renderer::Instance().DrawText("          D    RIGHT ARROW  ", 28, { 0,160 }, WHITE);
		}
		else if (timer > 6 && timer < 8 || timer > 14 && timer < 16)
		{
			pacman.Animate({ 104,136 }, 3, 0.1f, true);
			Renderer::Instance().DrawText("          S    DOWN ARROW   ", 28, { 0,160 }, WHITE);
		}
		Renderer::Instance().DrawText("  PRESS TAB TO INSERT COIN  ", 28, { 0,272 }, WHITE);
		break;
	case 2:
		ScreenManager::Instance().Render(0, WHITE);
		Renderer::Instance().DrawText("   1UP   HIGH SCORE   2UP  ", 28, { 0,0 }, WHITE);
		Renderer::Instance().DrawText("00", 2, { 40,8 }, WHITE);
		Renderer::Instance().DrawText("  CREDIT", 8, { 0,280 }, WHITE);
		Renderer::Instance().DrawNumber(coins,{72, 280}, WHITE);
		Renderer::Instance().DrawNumber(highscore, Renderer::Instance().AnchorNumberOnRight(highscore, { 128,8 }), WHITE);
		Renderer::Instance().DrawText("      PUSH START BUTTON      ", 28, { 0,136 }, 3);
		Renderer::Instance().DrawText(" BONUS PAC-MAN FOR 10000 : ", 28, { 0,184 }, 4);
		Renderer::Instance().DrawText("    ~ 1980 MIDWAY MFG.CO.   ", 28, { 0,208 }, 2);
		if(coins < 2) Renderer::Instance().DrawText("        1 PLAYER ONLY        ", 28, { 0,160 }, 1);
		else Renderer::Instance().DrawText("        1 OR 2 PLAYERS       ", 28, { 0,160 }, 1);
		break;
	case 3:
		ScreenManager::Instance().Render(1, 0);
		game->Render();
		break;
	case 4:
		break;
	default:
		break;
	}
	
}

void GameStateMachine::End()
{
	switch (currentState)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		game->End();
		delete game;
		break;
	case 4:
		break;

	default:
		break;
	}
	currentState = nextState;
}

void GameStateMachine::UseCoin()
{
	coins--;
}

bool GameStateMachine::HasCoins()
{
	return coins > 0;
}

bool GameStateMachine::IsSameState()
{
	return currentState == nextState?true:false;
}

GameStateMachine::GameStateMachine()
{
	currentState = 0;
	nextState = 0;
	coins = 0;
	timer = 0;
	highscore = FileReader::Instance().ReadHighScore();
	Animation pellet_ = { 1,2 };
	pellet_.sprites.push_back(19);
	pellet_.sprites.push_back(-1);
	pellet.animations.push_back(pellet_);
	Animation pacmanL = { 0,4 };
	pacmanL.sprites.push_back(0);
	pacmanL.sprites.push_back(17);
	pacmanL.sprites.push_back(16);
	pacmanL.sprites.push_back(17);
	pacman.animations.push_back(pacmanL);
	Animation pacmanR = { 0,4 };
	pacmanR.sprites.push_back(0);
	pacmanR.sprites.push_back(21);
	pacmanR.sprites.push_back(20);
	pacmanR.sprites.push_back(21);
	pacman.animations.push_back(pacmanR);
	Animation pacmanU = { 0,4 };
	pacmanU.sprites.push_back(0);
	pacmanU.sprites.push_back(15);
	pacmanU.sprites.push_back(14);
	pacmanU.sprites.push_back(15);
	pacman.animations.push_back(pacmanU);
	Animation pacmanD = { 0,4 };
	pacmanD.sprites.push_back(0);
	pacmanD.sprites.push_back(19);
	pacmanD.sprites.push_back(18);
	pacmanD.sprites.push_back(19);
	pacman.animations.push_back(pacmanD);
	Animation gv = { 0,2 };
	gv.sprites.push_back(36);
	gv.sprites.push_back(37);
	Animation bL = { 0,2 };
	bL.sprites.push_back(30);
	bL.sprites.push_back(31);
	b.animations.push_back(bL);
	b.animations.push_back(gv);
	Animation pL = { 0,2 };
	pL.sprites.push_back(44);
	pL.sprites.push_back(45);
	p.animations.push_back(pL);
	p.animations.push_back(gv);
	Animation iL = { 0,2 };
	iL.sprites.push_back(58);
	iL.sprites.push_back(59);
	i.animations.push_back(iL);
	i.animations.push_back(gv);
	Animation cL = { 0,2 };
	cL.sprites.push_back(72);
	cL.sprites.push_back(73);
	c.animations.push_back(cL);
	c.animations.push_back(gv);
}

GameStateMachine::~GameStateMachine()
{

}

int GameStateMachine::GetState()
{
	return nextState;
}

void GameStateMachine::SetState(const int state_)
{
	nextState = state_;
}

void GameStateMachine::Run()
{
	bool isMonitorHigher = GetMonitorHeight(GetCurrentMonitor()) > (36 / 28) * GetMonitorWidth(GetCurrentMonitor());
	int windowsSizeUsage = isMonitorHigher ? GetMonitorWidth(GetCurrentMonitor()) : GetMonitorHeight(GetCurrentMonitor());
	int tilemapSizeUsage = isMonitorHigher ? 8 * SCALE_FACTOR * 28 : 8 * SCALE_FACTOR * 36;
	int tilemapOffset = isMonitorHigher ? (8 * SCALE_FACTOR * (36 + 1)) : (8 * SCALE_FACTOR * (28 + 1));
	float scale = (float)windowsSizeUsage / (tilemapSizeUsage);
	float offset = (tilemapSizeUsage)-tilemapOffset;
	if (offset > 0)
		offset = (tilemapSizeUsage)-tilemapOffset - (GetMonitorHeight(GetCurrentMonitor()) / 2) + 224 * scale / 2;
	Camera2D camera = { 0 };
	camera.target = { 0,0 };
	camera.offset = { -offset * scale * 2 , 0 };
	camera.rotation = 0.0f;
	camera.zoom = scale;
	Start();
	
	while (nextState != -1 && !WindowShouldClose() && IsSameState())
	{
		AudioManager::Instance().Update(); 
		Input();
		Logic();
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode2D(camera);
		Render();
		DrawRectangle(-GetMonitorWidth(GetCurrentMonitor()), 0, GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), BLACK);
		DrawRectangle(224 * SCALE_FACTOR, 0, GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), BLACK);
		Debugger::Instance().Render();
		EndMode2D();
		EndDrawing();
	}
	End();
}
