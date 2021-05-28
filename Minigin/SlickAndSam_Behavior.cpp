#include "MiniginPCH.h"

#include "GridMovementComponent.h"
#include "SlickAndSam_Behavior.h"
#include "GameObject.h"
#include "Enums.h"

SlickAndSam_Behavior::SlickAndSam_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement)
	:IComponent{ owner }
	, m_pGridMovement{ gridMovement }
	, m_MaxMovementWait{ 1.f }
	, m_CurrentMovementWait{ 0.f }
{
	int spawnTile = std::rand() % 2 + 1;
	m_pGridMovement->SpawnOnTileIndex(spawnTile);

	m_pGridMovement->SetSpeed(150.f);
}

void SlickAndSam_Behavior::Update(float dt)
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
				m_pGridMovement->Move(EDirection::DownLeft);
			}
			else
			{
				m_pGridMovement->Move(EDirection::DownRight);
			}
		}
	}

	if (m_pGridMovement->RespawnAfterFall())
	{
		int spawnTile = std::rand() % 2 + 1;
		m_pGridMovement->SpawnOnTileIndex(spawnTile);
	}
}