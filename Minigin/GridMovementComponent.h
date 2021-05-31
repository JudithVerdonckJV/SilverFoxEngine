#pragma once
#include "IComponent.h"
#include "utils.h"
#include "Enums.h"

namespace fox
{
	class GameObject;
	class TextureComponent;
}

class PlayFieldComponent;
class DiscsComponent;

class GridMovementComponent final : public fox::IComponent
{
public:
	GridMovementComponent(fox::GameObject* owner, PlayFieldComponent* playfield, DiscsComponent* discs);
	~GridMovementComponent() = default;

	void Move(EDirection direction);
	void MoveToTop();
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
	DiscsComponent* m_pDiscs;

	FVector2 m_DesiredWorldPosition;
	int m_CurrentTileIndex;

	bool m_IsMoving;
	bool m_IsFalling;

	bool m_ArrivedOnTile;
	bool m_RespawnAfterFall;

	float m_MoveSpeed;
	FVector2 m_MoveDistance;
	EDirection m_LastDirection;

	bool m_UsingDisc;
	bool m_MovingToDisc;

	void MoveToFirstTile();
};