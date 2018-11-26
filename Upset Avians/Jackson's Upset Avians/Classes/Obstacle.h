#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Obstacle
{
public:
	Obstacle();
	Obstacle(Vec2 position, Vec2 size, Color4F color, PhysicsMaterial physicsMaterial = PHYSICSBODY_MATERIAL_DEFAULT);
	~Obstacle();
	DrawNode* getSprite();
	PhysicsBody* getPhysicsBody();
	Vec2 getPosition();
	static PhysicsMaterial wood;
	static PhysicsMaterial metal;
	static PhysicsMaterial stone;

private:
	DrawNode* sprite;
};