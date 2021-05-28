#include "MiniginPCH.h"
#include "Ugg_Behavior.h"

#include "GridMovementComponent.h"
#include "GameObject.h"
#include "Enums.h"

Ugg_Behavior::Ugg_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement)
	:IComponent{ owner }
	, m_pGridMovement{ gridMovement }
	, m_CurrentTileIndex{}
	, m_MaxMovementWait{1.f}
	, m_CurrentMovementWait{0.f}
{
	m_pGridMovement->SpawnOnTileIndex(27);
	m_pGridMovement->SetSpeed(100.f);
	m_CurrentTileIndex = m_pGridMovement->GetCurrentTileIndex();
}

void Ugg_Behavior::Update(float dt)
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
				m_pGridMovement->Move(EDirection::UpLeft);
			}
			else
			{
				m_pGridMovement->Move(EDirection::Left);
			}

			m_CurrentTileIndex = m_pGridMovement->GetCurrentTileIndex();
		}
	}
	


	if (m_pGridMovement->RespawnAfterFall())
	{
		m_pGridMovement->SpawnOnTileIndex(27);
		m_CurrentTileIndex = m_pGridMovement->GetCurrentTileIndex();
	}
}