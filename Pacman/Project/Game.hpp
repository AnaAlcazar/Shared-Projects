#pragma once
#include "ScreenManager.hpp"
#include "EntityManager.hpp"
class Game
{
private:
	int lives;
	int score;
    int highscore;
    int mode;
	int pointsLayout[36][28] = {
           {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
           {-1, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, -1, -1, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, -1},
           {-1, 19, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, 19, -1},
           {-1, 20, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, 20, -1},
           {-1, 19, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, 19, -1},
           {-1, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, -1},
           {-1, 19, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, 19, -1},
           {-1, 19, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, 19, -1},
           {-1, 19, 19, 19, 19, 19, 19, -1, -1, 19, 19, 19, 19, -1, -1, 19, 19, 19, 19, -1, -1, 19, 19, 19, 19, 19, 19, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, -1},
           {-1, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, -1, -1, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, -1},
           {-1, 19, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, 19, -1},
           {-1, 19, -1, -1, -1, -1, 19, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, 19, -1},
           {-1, 20, 19, 19, -1, -1, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, -1, -1, 19, 19, 20, -1},
           {-1, -1, -1, 19, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, 19, -1, -1, -1},
           {-1, -1, -1, 19, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, 19, -1, -1, -1},
           {-1, 19, 19, 19, 19, 19, 19, -1, -1, 19, 19, 19, 19, -1, -1, 19, 19, 19, 19, -1, -1, 19, 19, 19, 19, 19, 19, -1},
           {-1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1},
           {-1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1},
           {-1, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, -1},
           {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
           {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
	};
public:
    Game();
    void Start();
	void Input();
	void Logic();
	void Render();
    void ResetLayout();
    void RenderPoints();
    void EatDot();
    void End();
    ~Game();
};