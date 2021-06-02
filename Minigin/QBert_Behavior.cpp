#include "MiniginPCH.h"
#include "QBert_Behavior.h"

#include "GridMovementComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"

QBert_Behavior::QBert_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement)
	:IComponent{ owner }
	, m_pGridMovement{gridMovement}
	, m_pQBertTexture{}
	, m_CurrentTileIndex{}

	, HasDied{ false }
{
	m_pGridMovement->SpawnOnTileIndex(0);
	m_pGridMovement->SetSpeed(150.f);
	m_pQBertTexture = m_Owner->GetComponent<fox::TextureComponent>();
	m_CurrentTileIndex = m_pGridMovement->GetCurrentTileIndex();
}

void QBert_Behavior::Update(float )
{
	if (m_pGridMovement->HasArrivedOnTile())
	{
		m_pGridMovement->FlipTile();
		m_CurrentTileIndex = m_pGridMovement->GetCurrentTileIndex();

		SetIdleTexture();
	}

	if (m_pGridMovement->RespawnAfterFall())
	{
		HasDied = true;
		m_pGridMovement->SpawnOnTileIndex(0);
		m_CurrentTileIndex = m_pGridMovement->GetCurrentTileIndex();
	}
}

void QBert_Behavior::Reset()
{
	m_pGridMovement->SpawnOnTileIndex(0);
}

void QBert_Behavior::SetIdleTexture()
{
	EDirection currentDirection = m_pGridMovement->GetDirection();

	switch (currentDirection)
	{
	case EDirection::DownLeft:
		m_pQBertTexture->SetTexture("QBert/QBertDownLeft_Idle.png");
		break;
	case EDirection::DownRight:
		m_pQBertTexture->SetTexture("QBert/QBertDownRight_Idle.png");
		break;
	case EDirection::UpLeft:
		m_pQBertTexture->SetTexture("QBert/QBertUpLeft_Idle.png");
		break;
	case EDirection::UpRight:
		m_pQBertTexture->SetTexture("QBert/QBertUpRight_Idle.png");
		break;
	}
}