#pragma once
#include "IComponent.h"
#include "utils.h"
#include "Enums.h"

class GameObject;
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
	
	int m_CurrentRow;
	int m_CurrentTileIndex;

	FVector2 m_DesiredWorldPosition;

	bool m_IsMoving;

	float m_MoveSpeed;
	EDirection m_LastDirection;
};