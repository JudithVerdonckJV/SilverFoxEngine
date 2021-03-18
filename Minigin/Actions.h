#pragma once
#include "GameObject.h"

#include "IComponent.h"
#include "HealthComponent.h"

inline void Damage(fox::GameObject* object)
{
	fox::HealthComponent* health = object->GetComponent<fox::HealthComponent>();
	if (health != nullptr) health->DoDamage(1.f);
}

inline void ResetHealth(fox::GameObject* object)
{
	fox::HealthComponent* health = object->GetComponent<fox::HealthComponent>();
	if (health != nullptr) health->ResetHealth();
}