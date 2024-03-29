#include "GamePch.h"
#include "GridMovementComponent.h"

#include "GameObject.h"
#include "MathHelper.h"
#include "PlayFieldComponent.h"
#include "TextureComponent.h"
#include "DiscsComponent.h"

GridMovementComponent::GridMovementComponent(fox::GameObject* owner, PlayFieldComponent* playfield, DiscsComponent* discs)
	: IComponent{ owner }
	, m_ArrivedOnTile{}
	, m_pPlayfield{ playfield }
	, m_pDiscs{ discs }
	, m_DesiredWorldPosition{}
	, m_CurrentTileIndex{0}
	, m_IsMoving{ false }
	, m_IsFalling{ false }
	, m_RespawnAfterFall{ false }
	, m_MoveSpeed{100.f}
	, m_MoveDistance{}
	, m_LastDirection{ EDirection::DownRight }
	, m_UsingDisc{ false }
	, m_MovingToDisc{ false }
{
	m_MoveDistance = playfield->GetTileDistance();
	m_MoveDistance.x = std::abs(m_MoveDistance.x);
	m_MoveDistance.y = std::abs(m_MoveDistance.y);
}

void GridMovementComponent::Move(EDirection direction)
{
	if (m_IsMoving) return;

	FVector2 destination{ m_Owner->GetLocation() };

	switch (direction)
	{
	case EDirection::DownLeft:
		destination.x -= m_MoveDistance.x;
		destination.y += m_MoveDistance.y;
		break;
	case EDirection::DownRight:
		destination += m_MoveDistance;
		break;
	case EDirection::UpLeft:
		destination -= m_MoveDistance;
		break;
	case EDirection::UpRight:
		destination.x += m_MoveDistance.x;
		destination.y -= m_MoveDistance.y;
		break;
	case EDirection::Left:
		destination.x -= m_MoveDistance.x * 2.f;
		break;
	case EDirection::Right:
		destination.x += m_MoveDistance.x * 2.f;
		break;
	}

	bool onGrid{ m_pPlayfield->IsInsideTile(destination, m_CurrentTileIndex) };
	bool onDisc{ false };
	if (m_pDiscs) onDisc = m_pDiscs->IsInsideDisc(destination);

	if (!onGrid && !onDisc) m_IsFalling = true;
	if (onDisc) m_MovingToDisc = true;

	m_DesiredWorldPosition = destination;

	m_IsMoving = true;
	m_LastDirection = direction;
}

void GridMovementComponent::MoveToTop()
{
	m_IsMoving = true;
	m_UsingDisc = true;
	m_MovingToDisc = false;

	m_DesiredWorldPosition = m_pPlayfield->GetTilePositionAtIndex(0);
	m_DesiredWorldPosition.y -= m_pPlayfield->GetTileSize().y;
}

void GridMovementComponent::MoveToFirstTile()
{
	m_IsMoving = true;
	m_UsingDisc = false;

	m_pDiscs->DespawnActiveDisc();

	m_DesiredWorldPosition = m_pPlayfield->GetTilePositionAtIndex(0);
}

void GridMovementComponent::Update(float dt)
{
	if (!m_IsMoving) return;

	FVector2 newLocation = m_Owner->GetLocation();
	FVector2 direction = m_DesiredWorldPosition - newLocation;
	direction.Normalize();
	newLocation += direction * (m_MoveSpeed * dt);
	m_Owner->SetLocation(newLocation);
	if (m_UsingDisc) m_pDiscs->MoveActiveDisc(newLocation);

	if (EqualWithEpsilon(newLocation, m_DesiredWorldPosition, { 0.8f, 0.8f }))
	{
		if (m_MovingToDisc)
		{
			MoveToTop();
			return;
		}
		else if (m_UsingDisc)
		{
			MoveToFirstTile();
			return;
		}
		
		if (m_IsFalling)
		{
			m_IsFalling = false;
			m_RespawnAfterFall = true;
		}
		else
		{
			m_Owner->SetLocation(m_DesiredWorldPosition);
			m_ArrivedOnTile = true;
		}
		m_IsMoving = false;
	}
}

void GridMovementComponent::SpawnOnTileIndex(int index)
{
	m_Owner->SetLocation(m_pPlayfield->GetTilePositionAtIndex(index));
	m_ArrivedOnTile = true;
	m_RespawnAfterFall = false;
	m_IsMoving = false;
	m_IsFalling = false;
	m_CurrentTileIndex = index;
}

void GridMovementComponent::FlipTile()
{
	m_pPlayfield->FlipTileIndex(m_CurrentTileIndex);
	m_ArrivedOnTile = false;
}

void GridMovementComponent::UnflipTile()
{
	m_pPlayfield->UnflipTileIndex(m_CurrentTileIndex);
	m_ArrivedOnTile = false;
}

bool GridMovementComponent::HasArrivedOnTile() const
{
	return m_ArrivedOnTile;
}

void GridMovementComponent::SetSpeed(float speed)
{
	m_MoveSpeed = speed;
}

EDirection GridMovementComponent::GetDirection() const
{
	return m_LastDirection;
}

bool GridMovementComponent::IsMoving() const
{
	return m_IsMoving;
}

bool GridMovementComponent::RespawnAfterFall() const
{
	return m_RespawnAfterFall;
}

int GridMovementComponent::GetCurrentTileIndex() const
{
	return m_CurrentTileIndex;
}