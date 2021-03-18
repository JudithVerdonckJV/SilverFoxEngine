#include "MiniginPCH.h"
#include "ObserverManager.h"
#include "Observer.h"

fox::ObserverManager::~ObserverManager()
{
	for (Observer* observer : m_Observers)
	{
		delete observer;
	}
}

void fox::ObserverManager::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}