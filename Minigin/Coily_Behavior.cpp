#include "MiniginPCH.h"
#include "Coily_Behavior.h"

#include "GameObject.h"
#include "GridMovementComponent.h"
#include "TextureComponent.h"
#include "GameStatics.h"

Coily_Behavior::Coily_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement)
	: IComponent{ owner }
	, m_pGridMovement{ gridMovement }
	, m_CurrentMovementWait{}
	, m_MaxMovementWait{ 1.f }
	, m_IsEgg{ true }
{
	m_pGridMovement->SpawnOnTileIndex(0);
	m_pGridMovement->SetSpeed(150.f);
}

void Coily_Behavior::Update(float dt)
{
	if (m_pGridMovement->IsMoving()) return;
	
	m_CurrentMovementWait += dt;
	if (m_CurrentMovementWait <= m_MaxMovementWait) return;
	m_CurrentMovementWait = 0.f;
	
	if (m_IsEgg)
	{
		if (m_pGridMovement->HasArrivedOnTile())
		{
			int direction = std::rand() % 2;
			if (direction)
			{
				m_pGridMovement->Move(EDirection::DownLeft);
			}
			else
			{
				m_pGridMovement->Move(EDirection::DownRight);
			}
		}

		if (m_pGridMovement->RespawnAfterFall())
		{
			m_IsEgg = false;
			m_pGridMovement->SpawnOnTileIndex(0);
			m_Owner->GetComponent<fox::TextureComponent>()->SetTexture("Coily_Snake.png");
		}
	}
	else
	{
		if (m_pGridMovement->HasArrivedOnTile())
		{
			FVector2 playerPos{ fox::GameStatics::GetPlayerObject(0)->GetLocation() };
			FVector2 coilyPos{ m_Owner->GetLocation() };

			FVector2 direction{ playerPos - coilyPos };
			
			if (direction.x >= 0 && direction.y >= 0)
			{
				m_pGridMovement->Move(EDirection::DownRight);
			}
			else if (direction.x >= 0 && direction.y <= 0)
			{
				m_pGridMovement->Move(EDirection::UpRight);
			}
			else if (direction.x <= 0 && direction.y >= 0)
			{
				m_pGridMovement->Move(EDirection::DownLeft);
			}
			else
			{
				m_pGridMovement->Move(EDirection::UpLeft);
			}
		}

		if (m_pGridMovement->RespawnAfterFall())
		{
			m_IsEgg = true;
			m_pGridMovement->SpawnOnTileIndex(0);
			m_Owner->GetComponent<fox::TextureComponent>()->SetTexture("Coily_Egg.png");
		}
	}
}

void Coily_Behavior::Spawn()
{
	m_Owner->SetActive(true);
	m_Owner->SetVisibility(true);

	m_CurrentMovementWait = 0.f;
	m_IsEgg = true;
	m_Owner->GetComponent<fox::TextureComponent>()->SetTexture("Coily_Egg.png");

	m_pGridMovement->SpawnOnTileIndex(0);
}

void Coily_Behavior::Despawn()
{
	m_Owner->SetActive(false);
	m_Owner->SetVisibility(false);

	m_IsEgg = false;
	m_Owner->GetComponent<fox::TextureComponent>()->SetTexture("Coily_Snake.png");
}