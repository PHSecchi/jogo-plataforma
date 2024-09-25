#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "List.h"

class EntityList
{
private:
	List<Entity> list;
	int length;

public:
	EntityList();
	~EntityList();

	void includeEntity(Entity* entity);
	void removeEntity(Entity* entity);
	void removeAndDestroy(Entity* entity);
	void emptyList();
	void destroyEntities();
	void save();

	void draw();
	void update();

	void collide();

	bool isEmpty();
	int getLength() const;
};