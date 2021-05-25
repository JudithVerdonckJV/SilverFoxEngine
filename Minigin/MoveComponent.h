#pragma once
#include "IComponent.h"
#include "utils.h"

namespace fox
{
	class GameObject;

	class MoveComponent final : public IComponent
	{
	public:
		MoveComponent(GameObject* owner);
		virtual ~MoveComponent() = default;

		void AddMovementInput(float x, float y);
		void AddMovementInput(const FVector2& xy);
	};
}

