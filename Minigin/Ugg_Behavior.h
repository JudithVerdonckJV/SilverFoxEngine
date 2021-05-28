#pragma once
#include "IComponent.h"
#include "GridMovementComponent.h"

namespace fox
{
	class GameObject;
}

class Ugg_Behavior final : public fox::IComponent
{
public:
	Ugg_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement);
	~Ugg_Behavior() = default;

	virtual void Update(float dt) override;

private:
	GridMovementComponent* m_pGridMovement;
	int m_CurrentTileIndex;
	int m_CurrentDangerTileIndex;

	float m_MaxMovementWait;
	float m_CurrentMovementWait;
};
