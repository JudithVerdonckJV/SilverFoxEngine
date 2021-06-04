#pragma once
#include "IComponent.h"
#include "GridMovementComponent.h"

namespace fox
{
	class GameObject;
	class TextureComponent;
}

class SlickAndSam_Behavior : public fox::IComponent
{
public:
	SlickAndSam_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement, bool isSam);
	~SlickAndSam_Behavior() = default;

	virtual void Update(float dt) override;

	void Spawn();
	void Despawn();

private:
	GridMovementComponent* m_pGridMovement;
	fox::TextureComponent* m_pTexture;

	float m_MaxMovementWait;
	float m_CurrentMovementWait;
	bool m_IsSam;

	bool m_SetToIdle;

	void SetIdleTexture();
	void SetJumpingTexture();
};