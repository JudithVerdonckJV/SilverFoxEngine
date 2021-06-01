#include "MiniginPCH.h"
#include "SubjectComponent.h"
#include "GameObject.h"
#include "IObserver.h"
#include "ObserverManager.h"

fox::SubjectComponent::SubjectComponent(GameObject* owner)
	: IComponent{ owner }
	, m_pObservers{}
{
	
}

void fox::SubjectComponent::AddObserver(IObserver* observer)
{
	m_pObservers.push_back(observer);
}

void fox::SubjectComponent::RemoveObserver(fox::IObserver* observer)
{
	auto it = std::find(m_pObservers.begin(), m_pObservers.end(), observer);
	if (it != m_pObservers.end()) return;
	m_pObservers.erase(it);
}

void fox::SubjectComponent::Notify(fox::GameObject* gameObject, int eventName)
{
	for (fox::IObserver* observer : m_pObservers)
	{
		observer->OnNotify(gameObject, eventName);
	}
}
