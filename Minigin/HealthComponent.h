#pragma once
#include "IComponent.h"

namespace fox
{
	class GameObject;

	class HealthComponent : public IComponent
	{
	public:
		HealthComponent(GameObject* owner, float maxHealth);
		~HealthComponent() = default;

		float GetCurrentHealth() const { return m_CurrentHealth; };
		
		
		void DoDamage(float damage);
		void ResetHealth();

	private:
		float m_MaxHealth;
		float m_CurrentHealth;
	};
}


