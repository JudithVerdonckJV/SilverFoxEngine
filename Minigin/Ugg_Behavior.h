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

	void Spawn();
	void Despawn();

private:
	GridMovementComponent* m_pGridMovement;

	float m_MaxMovementWait;
	float m_CurrentMovementWait;
};
