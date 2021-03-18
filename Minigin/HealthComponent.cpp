#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"

fox::HealthComponent::HealthComponent(fox::GameObject* owner, float maxHealth)
	: IComponent{ owner }
	, m_MaxHealth{ maxHealth }
	, m_CurrentHealth{ maxHealth }
{
}

void fox::HealthComponent::DoDamage(float damage)
{
	if (m_CurrentHealth > 0)
	{
		m_CurrentHealth -= damage;
		m_Owner->pSubject->Notify(m_Owner, Event::HealthChange);
	}
}

void fox::HealthComponent::ResetHealth()
{
	m_CurrentHealth = m_MaxHealth;
	m_Owner->pSubject->Notify(m_Owner, Event::HealthChange);
}