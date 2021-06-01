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
	, m_NextDirection{ EDirection::UpLeft}
	, m_CalculatedNextDirection{ false }
{
	m_pGridMovement->SpawnOnTileIndex(0);
	m_pGridMovement->SetSpeed(150.f);
}

void Coily_Behavior::Update(float dt)
{
	if (m_pGridMovement->IsMoving()) return;
	
	if (m_IsEgg)
	{
		m_CurrentMovementWait += dt;
		if (m_CurrentMovementWait <= m_MaxMovementWait) return;
		m_CurrentMovementWait = 0.f;
		
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

		int currentTileIndex{ m_pGridMovement->GetCurrentTileIndex() };
		if (currentTileIndex >= 21 && currentTileIndex <= 27)
		{
			m_IsEgg = false;
			m_Owner->GetComponent<fox::TextureComponent>()->SetTexture("Coily_Snake.png");
			return;
		}
	}
	else
	{
		if (m_pGridMovement->HasArrivedOnTile())
		{
			if (!m_CalculatedNextDirection)
			{
				m_CalculatedNextDirection = true;
				
				FVector2 playerPos{ fox::GameStatics::GetPlayerObject(0)->GetLocation() };
				FVector2 coilyPos{ m_Owner->GetLocation() };

				FVector2 direction{ playerPos - coilyPos };

				if (direction.x <= 0 && direction.y <= 0)
				{
					m_NextDirection = EDirection::UpLeft;
				}
				else if (direction.x >= 0 && direction.y <= 0)
				{
					m_NextDirection = EDirection::UpRight;
				}
				else if (direction.x <= 0 && direction.y >= 0)
				{
					m_NextDirection = EDirection::DownLeft;
				}
				else
				{
					m_NextDirection = EDirection::DownRight;
				}
			}

			m_CurrentMovementWait += dt;
			if (m_CurrentMovementWait <= m_MaxMovementWait) return;
			m_CurrentMovementWait = 0.f;
			
			m_pGridMovement->Move(m_NextDirection);
			m_CalculatedNextDirection = false;
		}

		if (m_pGridMovement->RespawnAfterFall())
		{
			Spawn();
		}
	}
}

void Coily_Behavior::Spawn()
{
	m_Owner->SetActive(true);
	m_Owner->SetVisibility(true);

	m_CurrentMovementWait = 0.f;
	m_IsEgg = true;
	m_NextDirection = EDirection::UpLeft;
	m_Owner->GetComponent<fox::TextureComponent>()->SetTexture("Coily_Egg.png");

	m_pGridMovement->SpawnOnTileIndex(0);
}

void Coily_Behavior::Despawn()
{
	m_Owner->SetActive(false);
	m_Owner->SetVisibility(false);
}