#pragma once
#include "IComponent.h"
#include "utils.h"
#include "Enums.h"

namespace fox
{
	class GameObject;
}

class PlayFieldComponent;

class GridMovementComponent final : public fox::IComponent
{
public:
	GridMovementComponent(fox::GameObject* owner, PlayFieldComponent* playfield);
	~GridMovementComponent() = default;

	void Move(EDirection direction);
	EDirection GetDirection() const;
	void SetSpeed(float speed);


	virtual void Update(float deltaTime) override;

private:
	PlayFieldComponent* m_pPlayfield;

	FVector2 m_DesiredWorldPosition;

	bool m_IsMoving;
	bool m_IsFalling;

	float m_MoveSpeed;
	FVector2 m_MoveDistance;
	EDirection m_LastDirection;
};