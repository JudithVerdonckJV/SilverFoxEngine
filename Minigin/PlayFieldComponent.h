#pragma once
#include "IComponent.h"
#include "utils.h"

namespace fox
{
	class GameObject;
	class TextureComponent;
}


class PlayFieldComponent final : public fox::IComponent
{
public:
	PlayFieldComponent(fox::GameObject* owner, const std::string& assetPath);
	virtual ~PlayFieldComponent() = default;

	FVector2 GetTilePositionAtIndex(int index) const;
	int GetTileNr() const;
	FVector2 GetTileDistance() const;

	bool IsInsideTile(FVector2& destinationLocation);

private:
	std::string m_AssetPath;
	std::vector<FVector2> m_RelativePositions;
	std::vector<fox::TextureComponent*> m_pTileTextures;
	void ReadFile();

	const int m_Cols;
	const int m_TotalRows;
	int m_TileNr;


public:
	PlayFieldComponent(const PlayFieldComponent& other) = delete;
	PlayFieldComponent(PlayFieldComponent&& other) = delete;
	PlayFieldComponent& operator=(const PlayFieldComponent& other) = delete;
	PlayFieldComponent& operator=(PlayFieldComponent&& other) = delete;
};