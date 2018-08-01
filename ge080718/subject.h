#pragma once
#include <vector>
#include "observer.h"

class Subject 
{
	std::vector<Observer*> _observers;
public:
	Subject();
	void notify(const Entity* entity, const Message message) const;
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
};
