#pragma once
#include "stdafx.h"

template<class TL>
class List
{
private:
	template<class TE>
	class Item
	{
	private:
		Item<TE>* nextPtr;
		Item<TE>* prevPtr;
		TE* itemPtr;

	public:
		Item();
		~Item();
		void setNext(Item<TE>* next);
		Item<TE>* getNext() { return nextPtr; };
		void setPrev(Item<TE>* previous);
		Item<TE>* getPrev() { return prevPtr; };
		void setItem(TE* item);
		TE* getItem() { return itemPtr; };
	};

	Item<TL>* firstPtr;
	Item<TL>* lastPtr;
	Item<TL>* currentPtr;
public:
	List();
	~List();
	void includeItem(TL* item);
	void removeItem(TL* item);
	void removeAndDestroy(TL* item);
	void emptyList();
	TL* backToFirst();
	TL* goToNext();
};

template<class TL>
template<class TE>
inline List<TL>::Item<TE>::Item()
{
	prevPtr = nullptr;
	nextPtr = nullptr;
	itemPtr = nullptr;
}

template<class TL>
template<class TE>
inline List<TL>::Item<TE>::~Item()
{
	prevPtr = nullptr;
	nextPtr = nullptr;
	itemPtr = nullptr;
}

template<class TL>
template<class TE>
inline void List<TL>::Item<TE>::setNext(Item<TE>* next)
{
	nextPtr = next;
}

template<class TL>
template<class TE>
inline void List<TL>::Item<TE>::setPrev(Item<TE>* previous)
{
	prevPtr = previous;
}

template<class TL>
template<class TE>
inline void List<TL>::Item<TE>::setItem(TE* item)
{
	if (item != nullptr)
		itemPtr = item;
	else
	{
		cout << "Unable to set \"item\" in \"List.h\": null pointer." << endl;
		exit(1);
	}
}

template<class TL>
inline List<TL>::List()
{
	firstPtr = nullptr;
	lastPtr = nullptr;
	currentPtr = nullptr;
}

template<class TL>
inline List<TL>::~List()
{
}

template<class TL>
inline void List<TL>::includeItem(TL* item)
{
	if (item != nullptr)
	{
		Item<TL>* pAux = new Item<TL>();
		pAux->setItem(item);

		if (firstPtr == nullptr)
		{
			firstPtr = pAux;
			lastPtr = firstPtr;
		}
		else
		{
			lastPtr->setNext(pAux);
			pAux->setPrev(lastPtr);
			lastPtr = pAux;
		}
	}
	else
	{
		cout << "Unable to include item in \"List.h\": null pointer." << endl;
		exit(1);
	}
}

template<class TL>
inline void List<TL>::removeItem(TL* item)
{
	Item<TL>* pAux = firstPtr;

	while (pAux->getItem() != item)
	{
		pAux = pAux->getNext();
	}

	if (pAux == firstPtr)
	{
		firstPtr = pAux->getNext();
		if (firstPtr != nullptr)
			firstPtr->setPrev(nullptr);
	}
	else if (pAux == lastPtr)
	{
		lastPtr = lastPtr->getPrev();
		lastPtr->setNext(nullptr);
	}
	else
	{
		pAux->getPrev()->setNext(pAux->getNext());
		pAux->getNext()->setPrev(pAux->getPrev());
	}

	delete pAux;
}

template<class TL>
inline void List<TL>::removeAndDestroy(TL* item)
{
	Item<TL>* pAux = firstPtr;
	TL* itemPtr = nullptr;

	while (itemPtr != item)
	{
		pAux = pAux->getNext();
		itemPtr = pAux->getItem();
	}

	if (pAux == firstPtr)
	{
		firstPtr = pAux->getNext();
		if (firstPtr != nullptr)
			firstPtr->setPrev(nullptr);
	}
	else if (pAux == lastPtr)
	{
		lastPtr = lastPtr->getPrev();
		lastPtr->setNext(nullptr);
	}
	else
	{
		pAux->getPrev()->setNext(pAux->getNext());
		pAux->getNext()->setPrev(pAux->getPrev());
	}

	delete itemPtr;
	delete pAux;
}

template<class TL>
inline void List<TL>::emptyList()
{
	Item<TL>* pAux = firstPtr;

	while (pAux != nullptr)
	{
		firstPtr = pAux->getNext();
		delete pAux;
		pAux = firstPtr;
	}

	firstPtr = nullptr;
	lastPtr = nullptr;
	currentPtr = nullptr;
}

template<class TL>
inline TL* List<TL>::backToFirst()
{
	currentPtr = firstPtr;

	if (currentPtr != nullptr)
		return firstPtr->getItem();
	else
	{
		cout << "Unable to get first Item in \"List.h\": null pointer." << endl;
		return nullptr;
	}
}

template<class TL>
inline TL* List<TL>::goToNext()
{
	currentPtr = currentPtr->getNext();

	if (currentPtr != nullptr)
		return currentPtr->getItem();
	else
		return nullptr;
}