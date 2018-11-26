#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Character
{
public:
	Character();
	virtual ~Character();
	Character(Vec2 position, std::string spritePath);
	Sprite* getSprite();
	PhysicsBody* getBody();
	Vec2 getPosition();
	void kill(float delay = 0.0f);
protected:
	Sprite* sprite;
};