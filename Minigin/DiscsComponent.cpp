#include "MiniginPCH.h"
#include "DiscsComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "PlayFieldComponent.h"
#include "SubjectComponent.h"

#include "Enums.h"

DiscsComponent::DiscsComponent(fox::GameObject* owner, const std::string& , PlayFieldComponent* playfield)
	: IComponent{ owner }
	, m_ActiveDisc{ -1 }
	, m_pDiscTextures{}
{
	m_pDiscTextures.resize(2);
	m_pDiscLocations.resize(2);

	FVector2 leftDiscLocation{playfield->GetTilePositionAtIndex(10)};
	leftDiscLocation.x -= playfield->GetTileSize().x;
	m_pDiscLocations[0] = leftDiscLocation;
	
	FVector2 rightDiscLocation{ playfield->GetTilePositionAtIndex(14) };
	rightDiscLocation.x += playfield->GetTileSize().x;
	m_pDiscLocations[1] = rightDiscLocation;

	fox::GameObject* leftDiscObject{ new fox::GameObject{ m_Owner } };
	leftDiscObject->SetLocation(leftDiscLocation);
	m_pDiscTextures[0] = new fox::TextureComponent{ leftDiscObject };
	m_pDiscTextures[0]->SetTexture("Disc.png");
	m_pDiscTextures[0]->SetPivot();

	fox::GameObject* rightDiscObject{ new fox::GameObject{ m_Owner } };
	rightDiscObject->SetLocation(rightDiscLocation);
	m_pDiscTextures[1] = new fox::TextureComponent{ rightDiscObject };
	m_pDiscTextures[1]->SetTexture("Disc.png");
	m_pDiscTextures[1]->SetPivot();
}

bool DiscsComponent::IsInsideDisc(FVector2& destinationLocation)
{
	for (int i{}; i < 2; ++i)
	{
		if (!m_pDiscTextures[i]->GetOwner()->IsActive()) continue;
		
		FVector2 discLocation = m_pDiscTextures[i]->GetOwner()->GetLocation();
		FVector2 discUpperLeft{ discLocation.x - m_pDiscTextures[i]->GetWidth() / 2.f, discLocation.y + m_pDiscTextures[i]->GetHeight() / 2.f };
		FVector2 discBottomRight{ discLocation.x + m_pDiscTextures[i]->GetWidth() / 2.f, discLocation.y - m_pDiscTextures[i]->GetHeight() / 2.f };

		if (destinationLocation.x > discUpperLeft.x && destinationLocation.x < discBottomRight.x &&
			destinationLocation.y < discUpperLeft.y && destinationLocation.y > discBottomRight.y)
		{
			destinationLocation = discLocation;
			m_ActiveDisc = i;
			return true;
		}
	}

	return false;
}

void DiscsComponent::DespawnActiveDisc()
{
	m_pDiscTextures[m_ActiveDisc]->GetOwner()->SetActive(false);
	m_pDiscTextures[m_ActiveDisc]->GetOwner()->SetVisibility(false);
}

void DiscsComponent::MoveActiveDisc(const FVector2& location)
{
	m_pDiscTextures[m_ActiveDisc]->GetOwner()->SetLocation(location);
}

void DiscsComponent::Reset()
{
	for (int i{}; i < 2; ++i)
	{
		m_pDiscTextures[i]->GetOwner()->SetLocation(m_pDiscLocations[i]);
		m_pDiscTextures[i]->GetOwner()->SetActive(false);
		m_pDiscTextures[i]->GetOwner()->SetVisibility(false);
	}
	
	m_ActiveDisc = -1;
}

void DiscsComponent::ScoreRemainingDiscNr() const
{
	for (int i{}; i < 2; ++i)
	{
		if (m_pDiscTextures[i]->GetOwner()->IsActive())
		{
			m_Owner->GetComponent<fox::SubjectComponent>()->Notify(m_Owner, (int)EObserverEvents::RemainingDisc);
		}
	}
}