#pragma once
#include "cocos2d.h"
#include "character.h"
using namespace cocos2d;

enum birdState
{
	onSlingshot,
	airborne
};

class Bird : public Character
{
public:
	Bird(Vec2 position);
	birdState getState();
	void setState(birdState newState);
private:
	birdState state;
};