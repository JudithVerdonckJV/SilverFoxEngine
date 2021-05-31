#pragma once
#include "IComponent.h"
#include "GridMovementComponent.h"

class Wrongway_Behavior : public fox::IComponent
{
public:
	Wrongway_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement);
	~Wrongway_Behavior() = default;

	virtual void Update(float dt) override;

	void Spawn();
	void Despawn();

private:
	GridMovementComponent* m_pGridMovement;

	float m_MaxMovementWait;
	float m_CurrentMovementWait;
};