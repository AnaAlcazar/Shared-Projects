#include "Pacman.hpp"
#include "Renderer.hpp"
#include "GameStateMachine.hpp"
#include "Ghost.hpp"
#include "Levels.hpp"
#include <math.h>
#include <iostream>
#include "ScreenManager.hpp"

Pacman::Pacman() : Entity(Player, {13.5*8+4,26*8+4}, { -1, 0 }, 0.8f*SCALE_FACTOR, { 13.5f,26})
{
	pelletEffect = 0;
	pelletMultiplier = 0;
	scoreTimer = 0;
	Animation pUp={0,4};
	pUp.sprites.push_back(0);
	pUp.sprites.push_back(15);
	pUp.sprites.push_back(14);
	pUp.sprites.push_back(15);
	Animation pLeft = { 0,4 };
	pLeft.sprites.push_back(0);
	pLeft.sprites.push_back(17);
	pLeft.sprites.push_back(16);
	pLeft.sprites.push_back(17);
	Animation pDown = { 0,4 };
	pDown.sprites.push_back(0);
	pDown.sprites.push_back(19);
	pDown.sprites.push_back(18);
	pDown.sprites.push_back(19);
	Animation pRight = { 0,4 };
	pRight.sprites.push_back(0);
	pRight.sprites.push_back(21);
	pRight.sprites.push_back(20);
	pRight.sprites.push_back(21);
	Animation pDie = { 0,13 };
	pDie.sprites.push_back(0);
	pDie.sprites.push_back(1);
	pDie.sprites.push_back(2);
	pDie.sprites.push_back(3);
	pDie.sprites.push_back(4);
	pDie.sprites.push_back(5);
	pDie.sprites.push_back(6);
	pDie.sprites.push_back(7);
	pDie.sprites.push_back(8);
	pDie.sprites.push_back(9);
	pDie.sprites.push_back(10);
	pDie.sprites.push_back(11);
	pDie.sprites.push_back(-1);
	anim.animations.push_back(pUp);
	anim.animations.push_back(pLeft);
	anim.animations.push_back(pDown);
	anim.animations.push_back(pRight);
	anim.animations.push_back(pDie);
	Revive();
}

float Pacman::GetPelletEffect()
{
	return pelletEffect;
}

bool Pacman::HasPelletEffect()
{
	return pelletEffect > 0? true:false;
}

int Pacman::GetPelletMultiplier()
{
	return pelletMultiplier;
}

void Pacman::ResetPelletEffect()
{
	pelletEffect = 0;
	pelletMultiplier = 0;
}

void Pacman::Input()
{
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
	{
		TrySetDirection({ 0,-1 });
	}
	else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
	{
		TrySetDirection({ -1, 0 });
	}
	else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && !ScreenManager::Instance().YRestrictive(GetTileOfEntity()))
	{
		TrySetDirection({ 0, 1 });
	}
	else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
	{
		TrySetDirection({ 1, 0 });
	}
}

void Pacman::Logic()
{
	speed = LevelManager::Instance().RequestPacmanSpeed(HasPelletEffect(), GameStateMachine::Instance().game->IsInDotTile(GetTileOfEntity()));
	Entity::Move();

	if (pelletEffect > 0)pelletEffect -= GetFrameTime();
	else if (pelletEffect < 0)
		ResetPelletEffect();
	if (scoreTimer > 0 && GameStateMachine::Instance().game->GetStage() == 4)
	{
		scoreTimer -= GetFrameTime();
	}
	else if(GameStateMachine::Instance().game->GetStage() == 4)
		GameStateMachine::Instance().game->SetStage(1);
}

void Pacman::Render()
{
	if (GameStateMachine::Instance().game->GetStage() == 0)
	{
		Renderer::Instance().DrawSprite(0,{3,1}, position, WHITE);
	}
	if (GameStateMachine::Instance().game->GetStage() == 1)
	{
		if (direction.y == -1)anim.Animate(position, 0, 0.1f, true);
		else if (direction.x == -1)anim.Animate(position, 1, 0.1f, true);
		else if (direction.y == 1)anim.Animate(position, 2, 0.1f, true);
		else if (direction.x == 1)anim.Animate(position, 3, 0.1f, true);
	}
	else if (GameStateMachine::Instance().game->GetStage() == 3)
	{
		anim.Animate(position, 4, 0.2f, false);
	}
	else if (GameStateMachine::Instance().game->GetStage() == 4)
	{
		switch (pelletMultiplier - 1)
		{
		case 1:
			Renderer::Instance().DrawSprite(0, { 10,1 }, { position.x, position.y}, WHITE);
			break;
		case 2:
			Renderer::Instance().DrawSprite(0, { 12,0 }, { position.x, position.y}, WHITE);
			break;
		case 3:
			Renderer::Instance().DrawSprite(0, { 13,1 }, { position.x, position.y}, WHITE);
			break;
		case 4:
			Renderer::Instance().DrawSprite(0, { 13,3 }, { position.x, position.y}, WHITE);
			Renderer::Instance().DrawSprite(0, { 12,3 }, { position.x-8*2, position.y }, WHITE);
			break;
		default:
			break;
		}
	}
}

void Pacman::Kill()
{
	GameStateMachine::Instance().game->ResetTimer();
	AudioManager::Instance().PlaySoundByName("Eat_Ghost");
	GameStateMachine::Instance().game->SetStage(4);
	pelletMultiplier++;
	GameStateMachine::Instance().game->AddScore(100 * pow(2, pelletMultiplier));
}

void Pacman::Revive()
{
	alive = true;
	pelletEffect = 0;
}

bool Pacman::IsAlive()
{
	return alive;
}

void Pacman::Die()
{
	GameStateMachine::Instance().game->ResetTimer();
	alive = false;
	AudioManager::Instance().PlaySoundByName("Death");
	GameStateMachine::Instance().game->SetStage(3);
}

void Pacman::EatPellet()
{
	pelletEffect = LevelManager::Instance().RequestPelletTime();
	pelletMultiplier = 1;
	for (int i = 1; i < 5; i++)
	{
		dynamic_cast<Ghost*>(EntityManager::Instance().GetEntityAt(i))->ChangeMode(Ghost::Frightened);
		if(dynamic_cast<Ghost*>(EntityManager::Instance().GetEntityAt(i))->stage > 3)
			dynamic_cast<Ghost*>(EntityManager::Instance().GetEntityAt(i))->stage = 4;
	}
}

void Pacman::SetTargetTile(Vector2 tile)
{
}

Pacman::~Pacman()
{
}

