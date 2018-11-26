#include "character.h"
#include <iostream>
void Character::kill(float delay)
{
	//delays by the provided amount, and then removes the bird.
	sprite->runAction(Sequence::createWithTwoActions(DelayTime::create(delay), RemoveSelf::create()));
}
Character::Character() {}
Character::Character(Vec2 position, std::string texturePath)
{
	sprite = Sprite::create(texturePath); //Load the handle
	sprite->setPosition(position);
	sprite->setScale(0.25f); //Scale the bird since it loads in quite large 
	sprite->setAnchorPoint(Vec2(0.5f, 0.5f)); //Ensure the middle of the bird is the anchor point
	auto body = PhysicsBody::createCircle((sprite->getSpriteFrame()->getRectInPixels().size.height) * 0.5f * 0.65f); //Use a circle since the bird is roughly circular
	//auto body = PhysicsBody::createCircle(32.0f); //Use a circle since the bird is roughly circular
	std::cout << sprite->getSpriteFrame()->getRectInPixels().size.height * sprite->getScale() * 0.5f << std::endl;
	body->setContactTestBitmask(0xFFFFFFFF);
	sprite->setPhysicsBody(body); //Connect the physics body and the sprite
}

Sprite* Character::getSprite() {
	return sprite;
}

PhysicsBody* Character::getBody() {
	return sprite->getPhysicsBody();
}

Vec2 Character::getPosition() {
	return sprite->getPosition();
}

Character::~Character()
{
	//delete sprite;
	sprite = NULL;
}