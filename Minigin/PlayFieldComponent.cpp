#include "MiniginPCH.h"

#include <fstream>
#include <sstream>

#include "GameStatics.h"

#include "PlayFieldComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Transform.h"

using namespace fox;

PlayFieldComponent::PlayFieldComponent(GameObject* owner, const std::string& assetPath)
	:IComponent{ owner }
	, m_AssetPath{ assetPath }
	, m_RelativePositions{}
	, m_pTileTextures{}
	, m_TileNr{ }
	, m_Cols{ 7 }
	, m_TotalRows{ 7 }
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
			m_pTileTextures.push_back(texture);
			texture->SetTexture("SingleTile.png");
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

bool PlayFieldComponent::IsInsideTile(FVector2& destinationLocation)
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
			return true;
		}
	}

	return false;
}