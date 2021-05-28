#pragma once
#include "IComponent.h"
#include "GridMovementComponent.h"

namespace fox
{
	class GameObject;
}

class QBert_Behavior final : public fox::IComponent
{
public:
	QBert_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement);
	~QBert_Behavior() = default;

	virtual void Update(float dt) override;

private:
	GridMovementComponent* m_pGridMovement;
	int m_CurrentTileIndex;
};

