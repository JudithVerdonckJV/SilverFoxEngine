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

	void SpawnOnTileIndex(int index);
	bool RespawnAfterFall() const;

	void FlipTile();
	void UnflipTile();
	bool HasArrivedOnTile() const;
	bool IsMoving() const;

	int GetCurrentTileIndex() const;

private:
	PlayFieldComponent* m_pPlayfield;

	FVector2 m_DesiredWorldPosition;
	int m_CurrentTileIndex;

	bool m_IsMoving;
	bool m_IsFalling;

	bool m_ArrivedOnTile;
	bool m_RespawnAfterFall;

	float m_MoveSpeed;
	FVector2 m_MoveDistance;
	EDirection m_LastDirection;
};