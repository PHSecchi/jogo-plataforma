#pragma once
#include "stdafx.h"
#include "EntityList.h"
#include "CollisionManager.h"

class Thrower
{
protected:
	float limit;
	float cooldown;
	bool canThrowBool;
	CollisionManager* collisionManagerPtr;
	EntityList* entityListPtr;
public:
	Thrower(float t = 1.f);
	~Thrower();

	void setEntityList(EntityList* entityList);
	void setCollisionManager(CollisionManager* collisionManager);
	void canThrow(float t);
	void setLimit(float lim);
	void setCooldown(float cooldown);
	void setCanThrow(bool canThrow);
};