#include "MiniginPCH.h"

#include <fstream>
#include <sstream>

#include "GameStatics.h"

#include "PlayFieldComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Transform.h"
#include "TileData.h"

using namespace fox;

PlayFieldComponent::PlayFieldComponent(GameObject* owner, const std::string& assetPath, ETileBehavior tileBehavior)
	:IComponent{ owner }
	, m_AssetPath{ assetPath }
	, m_RelativePositions{}
	, m_pTileTextures{}
	, m_TileNr{ }
	, m_Cols{ 7 }
	, m_TotalRows{ 7 }
	, m_TileBehavior{ tileBehavior }
	, m_Stage0Path{ "TileStage0.png" }
	, m_Stage1Path{ "TileStage1.png" }
	, m_Stage2Path{ "TileStage2.png" }
{
	ReadFile();
	m_TileNr = (int)m_RelativePositions.size();
	
	int tilesPerRow{ 1 };
	int totalTiles{ 0 };
	float xOffset{ GameStatics::WINDOW_SIZE.x / 2.f };
	float yOffset{ 100.f };
	FVector2 currentPosition{};
	
	while (totalTiles < m_TileNr)
	{
		for (int i{}; i < tilesPerRow; ++i)
		{
			GameObject* tile{ new GameObject{ m_Owner } };
			TextureComponent* texture{ new TextureComponent{ tile } };
			TileData* tileData =  new TileData{ tile };

			m_pTileTextures.push_back(texture);
			m_pTileData.push_back(tileData);

			texture->SetTexture(m_Stage0Path);
			texture->SetPivot(0.5f, 0.5f);
			currentPosition = m_RelativePositions[totalTiles];
			currentPosition.x *= texture->GetWidth() / 2.f;
			currentPosition.x += xOffset;
			currentPosition.y *= texture->GetHeight() / 1.5f;
			currentPosition.y += yOffset;
			tile->SetTransform(currentPosition, { 0, 0 }, { 1, 1 });
			++totalTiles;
		}
		++tilesPerRow;
	}
}

void PlayFieldComponent::ReadFile()
{
	std::fstream layout{ m_AssetPath };
	if (!layout)
	{
		std::cout << "PlayFieldComponent, ReadFile: layout file couldn't be opened.\n";
		return;
	}

	while (!layout.eof())
	{
		std::string currentLine{};
		std::getline(layout, currentLine);

		if (currentLine.find("<tiles") != std::string::npos)
		{
			std::getline(layout, currentLine);
			while (currentLine != ">")
			{
				FVector2 temp{};
				std::string str{};
				std::stringstream stream{ currentLine };
				getline(stream, str, ' ');
				temp.x = stof(str);
				getline(stream, str);
				temp.y = stof(str);

				m_RelativePositions.push_back(temp);

				std::getline(layout, currentLine);
			}
		}
	}
}

FVector2 PlayFieldComponent::GetTilePositionAtIndex(int index) const
{
	fox::GameObject* tile{ m_Owner->GetChildByIndex(index) };

#ifdef _DEBUG
	if (tile == nullptr)
	{
		std::cout << "PlayfieldComponent, get tile position at index: index out of range.\n";
		return {};
	}
#endif

	return tile->GetLocation();
}

int PlayFieldComponent::GetTileNr() const
{
	return m_TileNr;
}

FVector2 PlayFieldComponent::GetTileDistance() const
{
	FVector2 location1{ m_Owner->GetChildByIndex(0)->GetLocation() };
	FVector2 location2{ m_Owner->GetChildByIndex(1)->GetLocation() };

	return location2 - location1;
}

FVector2 PlayFieldComponent::GetTileSize() const
{
	return m_pTileTextures[0]->GetDimensions();
}

bool PlayFieldComponent::IsInsideTile(FVector2& destinationLocation, int& index)
{
	for (int i{}; i < m_TileNr; ++i)
	{
		FVector2 tileLocation = m_Owner->GetChildByIndex(i)->GetLocation();
		FVector2 tileUpperLeft{tileLocation.x - m_pTileTextures[i]->GetWidth() / 2.f, tileLocation.y + m_pTileTextures[i]->GetHeight() / 2.f };
		FVector2 tileBottomRight{ tileLocation.x + m_pTileTextures[i]->GetWidth() / 2.f, tileLocation.y - m_pTileTextures[i]->GetHeight() / 2.f };

		if (destinationLocation.x > tileUpperLeft.x && destinationLocation.x < tileBottomRight.x &&
			destinationLocation.y < tileUpperLeft.y && destinationLocation.y > tileBottomRight.y)
		{
			destinationLocation = tileLocation;
			index = i;
			return true;
		}
	}

	return false;
}

void PlayFieldComponent::FlipTileIndex(int index)
{
	ETileType& type = m_pTileData[index]->Type;
	bool& finalStage = m_pTileData[index]->IsInFinalStage;

	switch (m_TileBehavior)
	{
	case ETileBehavior::OneFlip:
		if (type == ETileType::Stage1) return;
		type = ETileType::Stage1;
		finalStage = true;
		m_pTileTextures[index]->SetTexture(m_Stage1Path);
		break;

	case ETileBehavior::TwoFlips:
		if (type == ETileType::Stage2) return;
		else if (type == ETileType::Stage0)
		{
			type = ETileType::Stage1;
			m_pTileTextures[index]->SetTexture(m_Stage1Path);
		}
		else if (type == ETileType::Stage1)
		{
			type = ETileType::Stage2;
			finalStage = true;
			m_pTileTextures[index]->SetTexture(m_Stage2Path);
		}
		break;

	case ETileBehavior::CanUnflip:
		if (type == ETileType::Stage0)
		{
			type = ETileType::Stage1;
			finalStage = false;
			m_pTileTextures[index]->SetTexture(m_Stage1Path);
		}
		else if (type == ETileType::Stage1)
		{
			type = ETileType::Stage0;
			finalStage = true;
			m_pTileTextures[index]->SetTexture(m_Stage0Path);
		}
		break;
	}
}

void PlayFieldComponent::UnflipTileIndex(int index)
{
	ETileType& type = m_pTileData[index]->Type;
	bool& finalStage = m_pTileData[index]->IsInFinalStage;

	if (type == ETileType::Stage1)
	{
		type = ETileType::Stage0;
		finalStage = false;
		m_pTileTextures[index]->SetTexture(m_Stage0Path);
	}
	else if(type == ETileType::Stage2)
	{
		type = ETileType::Stage1;
		finalStage = false;
		m_pTileTextures[index]->SetTexture(m_Stage1Path);
	}
}

void PlayFieldComponent::CheckForLevelEnd()
{
	for (TileData* data : m_pTileData)
	{
		if (!data->IsInFinalStage)
		{
			m_LevelFinished = false;
			return;
		}
	}

	m_LevelFinished = true;
}

bool PlayFieldComponent::LevelFinished() const
{
	return m_LevelFinished;
}

void PlayFieldComponent::Reset()
{
	for (int i{}; i < m_TileNr; ++i)
	{
		m_pTileData[i]->Type = ETileType::Stage0;
		m_pTileData[i]->IsInFinalStage = false;
		m_pTileTextures[i]->SetTexture(m_Stage0Path);
	}

	m_LevelFinished = false;
}