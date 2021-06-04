#include "MiniginPCH.h"

#include "GridMovementComponent.h"
#include "TextureComponent.h"
#include "SlickAndSam_Behavior.h"
#include "GameObject.h"
#include "Enums.h"

SlickAndSam_Behavior::SlickAndSam_Behavior(fox::GameObject* owner, GridMovementComponent* gridMovement, bool isSam)
	:IComponent{ owner }
	, m_pGridMovement{ gridMovement }
	, m_pTexture{}
	, m_MaxMovementWait{ 1.f }
	, m_CurrentMovementWait{ 0.f }
	, m_IsSam{ isSam }
	, m_SetToIdle {true}
{
	m_pGridMovement->SetSpeed(100.f);
	m_pTexture = m_Owner->GetComponent<fox::TextureComponent>();
}

void SlickAndSam_Behavior::Update(float dt)
{
	if (m_pGridMovement->IsMoving()) return;

	if (m_pGridMovement->HasArrivedOnTile())
	{
		if (m_SetToIdle)
		{
			SetIdleTexture();
			m_SetToIdle = false;
		}

		m_CurrentMovementWait += dt;
		if (m_CurrentMovementWait <= m_MaxMovementWait) return;
		m_CurrentMovementWait = 0.f;

		m_pGridMovement->UnflipTile();
			
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


	if (m_pGridMovement->RespawnAfterFall())
	{
		int spawnTile = std::rand() % 2 + 1;
		m_pGridMovement->SpawnOnTileIndex(spawnTile);
	}
}

void SlickAndSam_Behavior::Spawn()
{
	m_Owner->SetActive(true);
	m_Owner->SetVisibility(true);

	m_CurrentMovementWait = 0.f;

	int spawnTile = std::rand() % 2 + 1;
	m_pGridMovement->SpawnOnTileIndex(spawnTile);
}

void SlickAndSam_Behavior::Despawn()
{
	m_Owner->SetActive(false);
	m_Owner->SetVisibility(false);
}

void SlickAndSam_Behavior::SetIdleTexture()
{
	std::string path{};
	if (m_IsSam) path = "SlickAndSam/Sam";
	else path = "SlickAndSam/Slick";

	EDirection direction = m_pGridMovement->GetDirection();

	switch (direction)
	{
	case EDirection::DownLeft:
		m_pTexture->SetTexture(path + "Left_Idle.png");
		break;
	case EDirection::DownRight:
		m_pTexture->SetTexture(path + "Right_Idle.png");
		break;
	}
}

void SlickAndSam_Behavior::SetJumpingTexture()
{
	std::string path{};
	if (m_IsSam) path = "SlickAndSam/Sam";
	else path = "SlickAndSam/Slick";

	EDirection direction = m_pGridMovement->GetDirection();

	switch (direction)
	{
	case EDirection::DownLeft:
		m_pTexture->SetTexture(path + "Left_Jump.png");
		break;
	case EDirection::DownRight:
		m_pTexture->SetTexture(path + "Right_Jump.png");
		break;
	}
}