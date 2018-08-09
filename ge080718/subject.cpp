#include "subject.h"
#include "globals.h"

Subject::Subject()
{
	_observers.reserve(10);
}

void Subject::notify(const Entity* entity, const Message message) const
{
	for (unsigned int i = 0; i < _observers.size(); ++i)
	{
		_observers[i]->onNotify(entity, message);
	}
}

void Subject::addObserver(Observer* observer)
{
	for (Observer* currentObserver : _observers)
	{
		if (currentObserver == observer)
		{
			Log::err("Observer already present!");
			return;
		}
	}
	_observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer)
{
	for (Observer* currentObserver : _observers)
	{
		if (currentObserver == observer)
		{
			//TODO: erase
			return;
		}
	}
}