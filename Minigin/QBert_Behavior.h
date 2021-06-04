#pragma once
#include "IComponent.h"
#include "GridMovementComponent.h"

namespace fox
{
	class GameObject;
	class TextureComponent;
}

class QBert_Behavior final : public fox::IComponent
{
public:
	QBert_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement);
	~QBert_Behavior() = default;

	virtual void Update(float dt) override;

	void Reset();
	void Die();

	void ChangeTexture(EDirection direction);
	void SetSpawnIndex(int index);

	bool HasDied;

private:
	GridMovementComponent* m_pGridMovement;
	fox::TextureComponent* m_pQBertTexture;
	int m_CurrentTileIndex;

	int m_SpawnIndex;
	void SetIdleTexture();
};

