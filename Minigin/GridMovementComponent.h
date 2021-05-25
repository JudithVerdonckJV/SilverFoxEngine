#pragma once
#include "IComponent.h"
#include "utils.h"

class GameObject;
class PlayFieldComponent;

enum class EDirection
{
	DownRight = 0,
	DownLeft = 1,
	UpRight = 2,
	UpLeft = 3,
};

class GridMovementComponent final : public fox::IComponent
{
public:
	GridMovementComponent(fox::GameObject* owner, PlayFieldComponent* playfield);
	~GridMovementComponent() = default;

	void Move(EDirection direction);

	virtual void Update(float deltaTime) override;

private:
	PlayFieldComponent* m_Playfield;
	
	IVector2 m_CurrentGridPosition;
	IVector2 m_DesiredGridPosition;
	//FVector2 m_CurrentWorldPosition; => owner transform component!

	bool m_IsMoving;
};