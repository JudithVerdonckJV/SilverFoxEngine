#pragma once
#include "IComponent.h"

class GridMovementComponent;
enum class EDirection;

namespace fox
{
	class GameObject;
	class TextureComponent;
}

class Coily_Behavior : public fox::IComponent
{
public:
	Coily_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement, fox::GameObject* qbertObject);
	~Coily_Behavior() = default;

	virtual void Update(float dt) override;

	void Spawn();
	void Despawn();

private:
	GridMovementComponent* m_pGridMovement;
	EDirection m_NextDirection;
	fox::TextureComponent* m_pTexture;

	fox::GameObject* m_pQBert;

	float m_MaxMovementWait;
	float m_CurrentMovementWait;

	bool m_IsEgg;
	bool m_CalculatedNextDirection;

	bool m_SetToIdle;
	void SetIdleTexture();
	void SetJumpingTexture();
};