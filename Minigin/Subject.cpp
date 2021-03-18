#include "MiniginPCH.h"
#include "Subject.h"
#include "GameObject.h"
#include "Observer.h"

void fox::Subject::AddObserver(Observer* observer)
{
	//auto it = std::find(m_Observers.begin(), m_Observers.end(), observer);
	//if (it != m_Observers.end()) return;
	m_Observers.push_back(observer);
}

void fox::Subject::RemoveObserver(fox::Observer* observer)
{
	auto it = std::find(m_Observers.begin(), m_Observers.end(), observer);
	if (it != m_Observers.end()) return;
	m_Observers.erase(it);
}

void fox::Subject::Notify(fox::GameObject* gameObject, Event eventName)
{
	for (fox::Observer* observer : m_Observers)
	{
		observer->OnNotify(gameObject, eventName);
	}
}