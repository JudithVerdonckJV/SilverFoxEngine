#pragma once
#include "GameObject.h"

#include "IComponent.h"
#include "GridMovementComponent.h"

#include "QBert_Behavior.h"
#include "Coily_Behavior.h"

#include "ServiceLocator.h"

inline void PlayASoundTEST(fox::GameObject*)
{
	ServiceLocator::GetSoundSystem().PlayEffect(0, 100);
}

inline void MoveDownLeft(fox::GameObject* owner)
{
	if (!static_cast<GridMovementComponent*>(owner->GetUserComponent())->IsMoving())
	{
		QBert_Behavior* qbert = owner->GetComponent<QBert_Behavior>();
		if (qbert) qbert->ChangeTexture(EDirection::DownLeft);
		Coily_Behavior* coily = owner->GetComponent<Coily_Behavior>();
		if (coily && coily->IsEgg()) return;
		if (coily) coily->ChangeTexture(EDirection::DownLeft);
	}
	static_cast<GridMovementComponent*>(owner->GetUserComponent())->Move(EDirection::DownLeft);
}

inline void MoveUpLeft(fox::GameObject* owner)
{
	if (!static_cast<GridMovementComponent*>(owner->GetUserComponent())->IsMoving())
	{
		QBert_Behavior* qbert = owner->GetComponent<QBert_Behavior>();
		if (qbert) qbert->ChangeTexture(EDirection::UpLeft);
		Coily_Behavior* coily = owner->GetComponent<Coily_Behavior>();
		if (coily && coily->IsEgg()) return;
		if (coily) coily->ChangeTexture(EDirection::UpLeft);
	}
	static_cast<GridMovementComponent*>(owner->GetUserComponent())->Move(EDirection::UpLeft);
}

inline void MoveDownRight(fox::GameObject* owner)
{
	if (!static_cast<GridMovementComponent*>(owner->GetUserComponent())->IsMoving())
	{
		QBert_Behavior* qbert = owner->GetComponent<QBert_Behavior>();
		if (qbert) qbert->ChangeTexture(EDirection::DownRight);
		Coily_Behavior* coily = owner->GetComponent<Coily_Behavior>();
		if (coily && coily->IsEgg()) return;
		if (coily) coily->ChangeTexture(EDirection::DownRight);
	}
	static_cast<GridMovementComponent*>(owner->GetUserComponent())->Move(EDirection::DownRight);
}

inline void MoveUpRight(fox::GameObject* owner)
{
	if (!static_cast<GridMovementComponent*>(owner->GetUserComponent())->IsMoving())
	{
		QBert_Behavior* qbert = owner->GetComponent<QBert_Behavior>();
		if (qbert) qbert->ChangeTexture(EDirection::UpRight);
		Coily_Behavior* coily = owner->GetComponent<Coily_Behavior>();
		if (coily && coily->IsEgg()) return;
		if (coily) coily->ChangeTexture(EDirection::UpRight);
	}
	static_cast<GridMovementComponent*>(owner->GetUserComponent())->Move(EDirection::UpRight);
}