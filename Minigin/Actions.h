#pragma once
#include "GameObject.h"

#include "IComponent.h"
#include "HealthComponent.h"
#include "GridMovementComponent.h"
#include "TextureComponent.h"

#include "ServiceLocator.h"

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

inline void PlayASoundTEST(fox::GameObject*)
{
	ServiceLocator::GetSoundSystem().PlayEffect(0, 100);
}

inline void MoveRight(fox::GameObject*)
{
	std::cout << "MOVING\n";
}

inline void MoveDownLeft(fox::GameObject* owner)
{
	if (!static_cast<GridMovementComponent*>(owner->GetUserComponent())->IsMoving())
	{
		owner->GetComponent<fox::TextureComponent>()->SetTexture("QBertDownLeft.png");
	}
	static_cast<GridMovementComponent*>(owner->GetUserComponent())->Move(EDirection::DownLeft);
}

inline void MoveUpLeft(fox::GameObject* owner)
{
	if (!static_cast<GridMovementComponent*>(owner->GetUserComponent())->IsMoving())
	{
		owner->GetComponent<fox::TextureComponent>()->SetTexture("QBertUpLeft.png");
	}
	static_cast<GridMovementComponent*>(owner->GetUserComponent())->Move(EDirection::UpLeft);
}

inline void MoveDownRight(fox::GameObject* owner)
{
	if (!static_cast<GridMovementComponent*>(owner->GetUserComponent())->IsMoving())
	{
		owner->GetComponent<fox::TextureComponent>()->SetTexture("QBertDownRight.png");
	}
	static_cast<GridMovementComponent*>(owner->GetUserComponent())->Move(EDirection::DownRight);
}

inline void MoveUpRight(fox::GameObject* owner)
{
	if (!static_cast<GridMovementComponent*>(owner->GetUserComponent())->IsMoving())
	{
		owner->GetComponent<fox::TextureComponent>()->SetTexture("QBertUpRight.png");
	}
	static_cast<GridMovementComponent*>(owner->GetUserComponent())->Move(EDirection::UpRight);
}