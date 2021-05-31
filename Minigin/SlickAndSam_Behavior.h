#pragma once
#include "IComponent.h"
#include "GridMovementComponent.h"

namespace fox
{
	class GameObject;
}

class SlickAndSam_Behavior : public fox::IComponent
{
public:
	SlickAndSam_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement);
	~SlickAndSam_Behavior() = default;

	virtual void Update(float dt) override;

	void Spawn();
	void Despawn();

private:
	GridMovementComponent* m_pGridMovement;

	float m_MaxMovementWait;
	float m_CurrentMovementWait;
};