#include "Bird.h"
#include "tags.h"

Bird::Bird(Vec2 position) : Character(position, "UA/Ship/SpaceShip.png")
{
	state = birdState::onSlingshot;
	sprite->getPhysicsBody()->setDynamic(false);
	sprite->getPhysicsBody()->setAngularDamping(0.5f);
	sprite->getPhysicsBody()->setTag(tags::bird);
}

birdState Bird::getState() {
	return state;
}

void Bird::setState(birdState newState) {
	state = newState;
}