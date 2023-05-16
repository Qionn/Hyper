#include "hyper/event/observer.h"
#include "hyper/event/subject.h"

namespace hyper
{
	void ASubject::AddObserver(IObserver* observer)
	{
		m_Observer.insert(observer);
	}

	void ASubject::RemoveObserver(IObserver* observer)
	{
		m_Observer.erase(observer);
	}

	void ASubject::NotifyObservers(const AEvent& event) const
	{
		for (IObserver* observer : m_Observer)
		{
			if (observer->OnEvent(event))
			{
				break;
			}
		}
	}
}
