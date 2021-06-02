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

	bool HasDied;

private:
	GridMovementComponent* m_pGridMovement;
	fox::TextureComponent* m_pQBertTexture;
	int m_CurrentTileIndex;

	void SetIdleTexture();
};

