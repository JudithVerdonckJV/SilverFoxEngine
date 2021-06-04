#include "MiniginPCH.h"
#include "Coily_Behavior.h"

#include "GameObject.h"
#include "GridMovementComponent.h"
#include "TextureComponent.h"
#include "SubjectComponent.h"
#include "GameStatics.h"

#include "Enums.h"

Coily_Behavior::Coily_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement, fox::GameObject* qbertObject, bool isPlayer)
	: IComponent{ owner }
	, m_pGridMovement{ gridMovement }
	, m_CurrentMovementWait{}
	, m_MaxMovementWait{ 1.f }
	, m_IsEgg{ true }
	, m_NextDirection{ EDirection::UpLeft}
	, m_CalculatedNextDirection{ false }
	, m_SetToIdle{ true }
	, m_IsPlayer{isPlayer}

	, m_pQBert{ qbertObject }
{
	m_pGridMovement->SpawnOnTileIndex(0);
	m_pGridMovement->SetSpeed(150.f);
	m_pTexture = m_Owner->GetComponent<fox::TextureComponent>();
}

void Coily_Behavior::Update(float dt)
{
	if (m_pGridMovement->IsMoving()) return;

	if (m_SetToIdle)
	{
		SetIdleTexture();
		m_SetToIdle = false;
	}
	
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

			SetJumpingTexture();
			m_SetToIdle = true;
		}

		int currentTileIndex{ m_pGridMovement->GetCurrentTileIndex() };
		if (currentTileIndex >= 21 && currentTileIndex <= 27)
		{
			m_IsEgg = false;
			m_Owner->GetComponent<fox::TextureComponent>()->SetTexture("Coily/CoilyUpLeft_Idle.png");
			return;
		}
	}
	else
	{
		if (m_pGridMovement->HasArrivedOnTile())
		{
			if (!m_IsPlayer) AIMovement(dt);
			else SetIdleTexture();
		}

		if (m_pGridMovement->RespawnAfterFall())
		{
			Spawn();
			m_Owner->GetComponent<fox::SubjectComponent>()->Notify(m_Owner, (int)EObserverEvents::CoilyDeath);
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
	m_Owner->GetComponent<fox::TextureComponent>()->SetTexture("Coily/CoilyEgg_Idle.png");

	m_pGridMovement->SpawnOnTileIndex(0);
}

void Coily_Behavior::Despawn()
{
	m_Owner->SetActive(false);
	m_Owner->SetVisibility(false);
}

void Coily_Behavior::SetIdleTexture()
{
	if (m_IsEgg)
	{
		m_pTexture->SetTexture("Coily/CoilyEgg_Idle.png");
		return;
	}
	
	EDirection direction = m_pGridMovement->GetDirection();

	switch (direction)
	{
	case EDirection::DownLeft:
		m_pTexture->SetTexture("Coily/CoilyDownLeft_Idle.png");
		break;
	case EDirection::DownRight:
		m_pTexture->SetTexture("Coily/CoilyDownRight_Idle.png");
		break;
	case EDirection::UpLeft:
		m_pTexture->SetTexture("Coily/CoilyUpLeft_Idle.png");
		break;
	case EDirection::UpRight:
		m_pTexture->SetTexture("Coily/CoilyUpRight_Idle.png");
		break;
	}
}

void Coily_Behavior::SetJumpingTexture()
{
	if (m_IsEgg)
	{
		m_pTexture->SetTexture("Coily/CoilyEgg_Jump.png");
		return;
	}

	EDirection direction = m_pGridMovement->GetDirection();

	switch (direction)
	{
	case EDirection::DownLeft:
		m_pTexture->SetTexture("Coily/CoilyDownLeft_Jump.png");
		break;
	case EDirection::DownRight:
		m_pTexture->SetTexture("Coily/CoilyDownRight_Jump.png");
		break;
	case EDirection::UpLeft:
		m_pTexture->SetTexture("Coily/CoilyUpLeft_Jump.png");
		break;
	case EDirection::UpRight:
		m_pTexture->SetTexture("Coily/CoilyUpRight_Jump.png");
		break;
	}
}

void Coily_Behavior::ChangeTexture(EDirection direction)
{
	switch (direction)
	{
	case EDirection::DownLeft:
		m_pTexture->SetTexture("Coily/CoilyDownLeft_Jump.png");
		break;
	case EDirection::DownRight:
		m_pTexture->SetTexture("Coily/CoilyDownRight_Jump.png");
		break;
	case EDirection::UpLeft:
		m_pTexture->SetTexture("Coily/CoilyUpLeft_Jump.png");
		break;
	case EDirection::UpRight:
		m_pTexture->SetTexture("Coily/CoilyUpRight_Jump.png");
		break;
	}
}

void Coily_Behavior::AIMovement(float dt)
{
	if (!m_CalculatedNextDirection)
	{
		m_CalculatedNextDirection = true;

		FVector2 playerPos{ m_pQBert->GetLocation() };
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
	SetJumpingTexture();
	m_SetToIdle = true;
}

bool Coily_Behavior::IsEgg() const
{
	return m_IsEgg;
}