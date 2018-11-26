#include "Pig.h"
#include "tags.h"

//Pig constructor, calls character constructor and then sets pig-specific properties
Pig::Pig(Vec2 position) : Character(position, "UA/Ship/asteroid.png")
{
	health = 4;
	sprite->getPhysicsBody()->setAngularDamping(0.5f);
	sprite->getPhysicsBody()->setTag(tags::pig);
}

//Returns the pig's health
int Pig::getHealth() {
	return health;
}

//Sets the pig's health to the provided amount
void Pig::setHealth(int newHealth) {
	health = newHealth;
}

//Damages the pig by the provided amount. calling damage() will default to 1 damage. eg: pig.damage() will do 1 damage, pig.damage(2) will do 2 damage.
void Pig::damage(int amount) {
	health -= amount;
}

//Checks if the pig's health is equal or less than 0, if it is we kill the pig.
bool Pig::shouldDie()
{
	if (health <= 0)
	{
		kill();
		return true;
	}
	return false;
}