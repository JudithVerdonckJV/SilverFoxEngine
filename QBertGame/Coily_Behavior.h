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
	Coily_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement, fox::GameObject* qbertObject, bool isPlayer);
	~Coily_Behavior() = default;

	virtual void Update(float dt) override;

	void Spawn();
	void Despawn();

	void ChangeTexture(EDirection direction);

	bool IsEgg() const;

private:
	GridMovementComponent* m_pGridMovement;
	EDirection m_NextDirection;
	fox::TextureComponent* m_pTexture;

	fox::GameObject* m_pQBert;

	float m_MaxMovementWait;
	float m_CurrentMovementWait;

	bool m_IsEgg;
	bool m_CalculatedNextDirection;
	bool m_IsPlayer;

	bool m_SetToIdle;
	void SetIdleTexture();
	void SetJumpingTexture();

	void AIMovement(float dt);
};