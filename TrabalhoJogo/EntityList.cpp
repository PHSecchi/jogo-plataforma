#include "EntityList.h"

EntityList::EntityList() :
	list(),
	length(0)
{
}

EntityList::~EntityList()
{
}

void EntityList::includeEntity(Entity* entity)
{
	list.includeItem(entity);
	length++;
}

void EntityList::removeEntity(Entity* entity)
{
	list.removeItem(entity);
	length--;
}

void EntityList::removeAndDestroy(Entity* entity)
{
	list.removeAndDestroy(entity);
}

void EntityList::emptyList()
{
	list.emptyList();
}

void EntityList::destroyEntities()
{
	Entity* e = list.backToFirst();

	while (e != nullptr)
	{
		if (e == nullptr)
		{
			cout << "Unable to delete entity in \"EntityList.cpp\": null pointer." << endl;
			exit(1);
		}

		delete e;
		e = list.goToNext();
	}

	list.emptyList();
	length = 0;
}

void EntityList::update()
{
	Entity* e = list.backToFirst();

	while (e != nullptr)
	{
		e->update();
		e = list.goToNext();
	}
}

void EntityList::draw()
{
	Entity* e = list.backToFirst();

	while (e != nullptr)
	{
		e->draw();
		e = list.goToNext();
	}
}

void EntityList::collide()
{
	Entity* e = list.backToFirst();
}

bool EntityList::isEmpty()
{
	if (length > 0)
		return false;
	else
		return true;
}

int EntityList::getLength() const
{
	return length;
}

void EntityList::save()
{
	Entity* e = list.backToFirst();
	e->clearSaveFiles();

	while (e != nullptr)
	{
		e->save();
		e = list.goToNext();
	}
}