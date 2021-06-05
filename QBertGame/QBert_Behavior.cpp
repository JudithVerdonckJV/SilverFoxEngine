#include "GamePch.h"
#include "QBert_Behavior.h"

#include "ServiceLocator.h"

#include "GridMovementComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"

QBert_Behavior::QBert_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement)
	:IComponent{ owner }
	, m_pGridMovement{gridMovement}
	, m_pQBertTexture{}
	, m_CurrentTileIndex{}

	, HasDied{ false }
	, m_SpawnIndex{0}
{
	m_pGridMovement->SpawnOnTileIndex(m_SpawnIndex);
	m_pGridMovement->SetSpeed(150.f);
	m_pQBertTexture = m_Owner->GetComponent<fox::TextureComponent>();
}

void QBert_Behavior::Update(float )
{
	if (m_pGridMovement->HasArrivedOnTile())
	{
		m_pGridMovement->FlipTile();

		SetIdleTexture();
	}

	if (m_pGridMovement->RespawnAfterFall())
	{
		Die();
	}
}

void QBert_Behavior::Reset()
{
	m_pGridMovement->SpawnOnTileIndex(m_SpawnIndex);
	HasDied = false;
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

void QBert_Behavior::Die()
{
	Reset();
	HasDied = true;
}

void QBert_Behavior::ChangeTexture(EDirection direction)
{
	//ServiceLocator::GetSoundSystem().PlayEffect((int)ESounds::QBertJump, 1.f);
	
	switch (direction)
	{
	case EDirection::DownLeft:
		m_pQBertTexture->SetTexture("QBert/QBertDownLeft_Jump.png");
		break;
	case EDirection::DownRight:
		m_pQBertTexture->SetTexture("QBert/QBertDownRight_Jump.png");
		break;
	case EDirection::UpLeft:
		m_pQBertTexture->SetTexture("QBert/QBertUpLeft_Jump.png");
		break;
	case EDirection::UpRight:
		m_pQBertTexture->SetTexture("QBert/QBertUpRight_Jump.png");
		break;
	}
}

void QBert_Behavior::SetSpawnIndex(int index)
{
	m_SpawnIndex = index;
}