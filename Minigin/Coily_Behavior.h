#pragma once
#include "IComponent.h"

class GridMovementComponent;

namespace fox
{
	class GameObject;
}

class Coily_Behavior : public fox::IComponent
{
public:
	Coily_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement);
	~Coily_Behavior() = default;

	virtual void Update(float dt) override;

	void Spawn();
	void Despawn();

private:
	GridMovementComponent* m_pGridMovement;

	float m_MaxMovementWait;
	float m_CurrentMovementWait;

	bool m_IsEgg;
};