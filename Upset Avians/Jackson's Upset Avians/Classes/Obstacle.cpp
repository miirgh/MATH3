#include "Obstacle.h"
#include "tags.h"
/* 	wood = PhysicsMaterial(0.2f, 0.2f, 0.6f);
	stone = PhysicsMaterial(0.3f, 0.2f, 0.7f);*/
PhysicsMaterial Obstacle::wood = PhysicsMaterial(0.2f, 0.2f, 0.6f);
PhysicsMaterial Obstacle::stone = PhysicsMaterial(0.3f, 0.2f, 0.7f);

Obstacle::Obstacle() {}

Obstacle::~Obstacle() {}

Obstacle::Obstacle(Vec2 position, Vec2 size, Color4F color, PhysicsMaterial physicsMaterial)
{
	sprite = DrawNode::create();
	
	sprite->drawSolidRect(-size * 0.5, size * 0.5, color);
	sprite->setPosition(position);
	

	auto body = PhysicsBody::createBox(cocos2d::Size(size.x, size.y));
	body->setContactTestBitmask(0xFFFFFFFF);
	body->setTag(obstacle);
	sprite->setPhysicsBody(body);
}

DrawNode* Obstacle::getSprite() {
	return sprite;
}

PhysicsBody* Obstacle::getPhysicsBody() {
	return sprite->getPhysicsBody();
}

Vec2 Obstacle::getPosition() {
	return sprite->getPosition();
}