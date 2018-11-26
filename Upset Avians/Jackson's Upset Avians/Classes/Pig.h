#pragma once
#include "character.h"
class Pig : public Character
{
public:
	Pig(Vec2 position);
	int getHealth();
	void setHealth(int newHealth);
	void damage(int amount = 1);
	bool shouldDie();
private:
	int health;
};