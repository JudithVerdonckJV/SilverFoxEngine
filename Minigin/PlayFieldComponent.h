#pragma once
#include "IComponent.h"
#include "utils.h"
#include "Enums.h"

namespace fox
{
	class GameObject;
	class TextureComponent;
}

class TileData;


class PlayFieldComponent final : public fox::IComponent
{
public:
	PlayFieldComponent(fox::GameObject* owner, const std::string& assetPath, ETileBehavior tileBehavior);
	virtual ~PlayFieldComponent() = default;

	FVector2 GetTilePositionAtIndex(int index) const;
	int GetTileNr() const;
	FVector2 GetTileDistance() const;

	bool IsInsideTile(FVector2& destinationLocation, int& index);

	void FlipTileIndex(int index);
	void UnflipTileIndex(int index);

	void CheckForLevelEnd();

private:
	std::string m_AssetPath;
	std::vector<FVector2> m_RelativePositions;
	std::vector<fox::TextureComponent*> m_pTileTextures;
	std::vector<TileData*> m_pTileData;
	void ReadFile();

	const int m_Cols;
	const int m_TotalRows;
	int m_TileNr;

	ETileBehavior m_TileBehavior;
	std::string m_Stage0Path;
	std::string m_Stage1Path;
	std::string m_Stage2Path;

	bool m_LevelFinished;

public:
	PlayFieldComponent(const PlayFieldComponent& other) = delete;
	PlayFieldComponent(PlayFieldComponent&& other) = delete;
	PlayFieldComponent& operator=(const PlayFieldComponent& other) = delete;
	PlayFieldComponent& operator=(PlayFieldComponent&& other) = delete;
};