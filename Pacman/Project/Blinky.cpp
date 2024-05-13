#include "Blinky.hpp"

Blinky::Blinky()
{
	Animation u{ 0,2 };
	u.sprites.push_back(32);
	u.sprites.push_back(33);

	Animation l{ 0,2 };
	l.sprites.push_back(30);
	l.sprites.push_back(31);

	Animation d{ 0,2 };
	d.sprites.push_back(34);
	d.sprites.push_back(35);

	Animation r{ 0,2 };
	r.sprites.push_back(28);
	r.sprites.push_back(29);

	Animation f{ 0,2 };
	f.sprites.push_back(36);
	f.sprites.push_back(37);

	anim.animations.push_back(u);
	anim.animations.push_back(l);
	anim.animations.push_back(d);
	anim.animations.push_back(r);
	anim.animations.push_back(f);
}

void Blinky::Render()
{
	if (alive)
	{
		if (ghostMode == Ghost::Frightened)
		{
			anim.Animate(position, 4, 0.1f, true);
		}
		else
		{
			if (direction.x == 0 && direction.y == -1)anim.Animate(position, 0, 0.1f, true);
			else if (direction.x == -1 && direction.y == 0)anim.Animate(position, 1, 0.1f, true);
			else if (direction.x == 0 && direction.y == 1)anim.Animate(position, 2, 0.1f, true);
			else if (direction.x == 1 && direction.y == 0)anim.Animate(position, 3, 0.1f, true);
		}
	}
	else
	{
		if (direction.x == 0 && direction.y == -1) Renderer::Instance().DrawSprite(0, {8,5}, position, WHITE);
		else if (direction.x == -1 && direction.y == 0) Renderer::Instance().DrawSprite(0, {9,4}, position, WHITE);
		else if (direction.x == 0 && direction.y == 1) Renderer::Instance().DrawSprite(0, {9,5}, position, WHITE);
		else if (direction.x == 1 && direction.y == 0) Renderer::Instance().DrawSprite(0, {8,4}, position, WHITE);
	}
}

void Blinky::Brain()
{
	Vector2 tileGo = { 0,0 };
	switch (ghostMode)
	{
	case Ghost::Scatter:
		tileGo = { 25,0 };
		break;
	case Ghost::Chase:
		tileGo = EntityManager::Instance().GetEntityAt(0)->GetTileOfEntity();
		break;
	case Ghost::Frightened:
		tileGo = { (float)((int)(rand() % 28)), (float)((int)(rand() % 31+3)) };
		break;
	default:
		break;
	}
	SetTargetTile(tileGo);
}