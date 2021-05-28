#include "MiniginPCH.h"
#include "QBert_Behavior.h"

#include "GridMovementComponent.h"
#include "GameObject.h"

QBert_Behavior::QBert_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement)
	:IComponent{ owner }
	, m_pGridMovement{gridMovement}
	, m_CurrentTileIndex{}
{
	m_pGridMovement->SpawnOnTileIndex(0);
	m_CurrentTileIndex = m_pGridMovement->GetCurrentTileIndex();
}

void QBert_Behavior::Update(float )
{
	if (m_pGridMovement->HasArrivedOnTile())
	{
		m_pGridMovement->FlipTile();
		m_CurrentTileIndex = m_pGridMovement->GetCurrentTileIndex();
	}

	if (m_pGridMovement->RespawnAfterFall())
	{
		m_pGridMovement->SpawnOnTileIndex(0);
		m_CurrentTileIndex = m_pGridMovement->GetCurrentTileIndex();
	}
}
