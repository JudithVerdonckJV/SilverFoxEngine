#include "MiniginPCH.h"
#include "ObserverManager.h"
#include "IObserver.h"

fox::ObserverManager::~ObserverManager()
{
	for (IObserver* observer : m_Observers)
	{
		delete observer;
	}
}

void fox::ObserverManager::AddObserver(IObserver* observer)
{
	m_Observers.push_back(observer);
}