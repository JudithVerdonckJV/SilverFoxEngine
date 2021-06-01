#pragma once
#include "IComponent.h"
#include "utils.h"

namespace fox
{
	class GameObject;
	class TextureComponent;
}

class PlayFieldComponent;

class DiscsComponent : public fox::IComponent
{
public:
	DiscsComponent(fox::GameObject* owner, const std::string& assetPath, PlayFieldComponent* playfield);
	virtual ~DiscsComponent() = default;

	bool IsInsideDisc(FVector2& destinationLocation);

	void DespawnActiveDisc();
	void MoveActiveDisc(const FVector2& location);

	void Reset();

private:
	int m_ActiveDisc;
	std::vector<fox::TextureComponent*> m_pDiscTextures;
	std::vector<FVector2> m_pDiscLocations;
};