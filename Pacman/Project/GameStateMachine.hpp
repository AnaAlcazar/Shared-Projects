#pragma once
#include "ScreenManager.hpp"
#include "EntityManager.hpp"
#include "FileReader.hpp"
#include "Game.hpp"
class GameStateMachine
{
private:
	Animator pellet;
	Animator pacman;
	Animator b;
	Animator p;
	Animator i;
	Animator c;
	int currentState;
	int nextState;
	int coins;
	float timer;
	int highscore;
	void Start();
	void Input();
	void Logic();
	void Render();
	void End();
	
	bool IsSameState();
	GameStateMachine();
	~GameStateMachine();
public:
	static GameStateMachine& Instance()
	{
		static GameStateMachine instance;
		return instance;
	};
	Game* game;
	int GetState();
	void SetState(const int state_);
	void Run();
	void UseCoin();
	bool HasCoins();
};