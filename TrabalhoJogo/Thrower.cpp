#include "stdafx.h"
#include "Thrower.h"

Thrower::Thrower(float t):
	limit(t - 0.7f),
	canThrowBool(false),
	cooldown(0.f)
{
	entityListPtr = nullptr;
	collisionManagerPtr = nullptr;
}

Thrower::~Thrower()
{
	entityListPtr = nullptr;
}

void Thrower::setEntityList(EntityList* entityList)
{
	entityListPtr = entityList;
}

void Thrower::setCollisionManager(CollisionManager* collisionManager)
{
	if (collisionManager != nullptr)
		collisionManagerPtr = collisionManager;
}

void Thrower::canThrow(float t)
{
	if (t >= limit)
		canThrowBool = true;
}

void Thrower::setLimit(float lim)
{
	limit = lim;
}

void Thrower::setCooldown(float cooldown)
{
	this->cooldown = cooldown;
}

void Thrower::setCanThrow(bool canThrow)
{
	canThrowBool = canThrow;
}