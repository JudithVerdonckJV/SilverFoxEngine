#include "MiniginPCH.h"
#include "Wrongway_Behavior.h"
#include "GridMovementComponent.h"
#include "GameObject.h"
#include "Enums.h"

Wrongway_Behavior::Wrongway_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement)
	:IComponent{ owner }
	, m_pGridMovement{ gridMovement }
	, m_MaxMovementWait{ 1.f }
	, m_CurrentMovementWait{ 0.f }
{
	m_pGridMovement->SpawnOnTileIndex(21);
	m_pGridMovement->SetSpeed(100.f);
}

void Wrongway_Behavior::Update(float dt)
{
	if (m_pGridMovement->IsMoving()) return;

	m_CurrentMovementWait += dt;
	if (m_CurrentMovementWait >= m_MaxMovementWait)
	{
		m_CurrentMovementWait = 0.f;

		if (m_pGridMovement->HasArrivedOnTile())
		{
			int direction = std::rand() % 2;
			if (direction)
			{
				m_pGridMovement->Move(EDirection::UpRight);
			}
			else
			{
				m_pGridMovement->Move(EDirection::Right);
			}
		}
	}

	if (m_pGridMovement->RespawnAfterFall())
	{
		m_pGridMovement->SpawnOnTileIndex(21);
	}
}

void Wrongway_Behavior::Spawn()
{
	m_Owner->SetActive(true);
	m_Owner->SetVisibility(true);

	m_CurrentMovementWait = 0.f;
	m_pGridMovement->SpawnOnTileIndex(21);
}

void Wrongway_Behavior::Despawn()
{
	m_Owner->SetActive(false);
	m_Owner->SetVisibility(false);
}