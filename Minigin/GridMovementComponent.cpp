#include "MiniginPCH.h"
#include "GridMovementComponent.h"

#include"GameObject.h"
#include "MathHelper.h"
#include "PlayFieldComponent.h"

GridMovementComponent::GridMovementComponent(fox::GameObject* owner, PlayFieldComponent* playfield)
	: IComponent{ owner }
	, m_ArrivedOnTile{}
	, m_pPlayfield{ playfield }
	, m_DesiredWorldPosition{}
	, m_CurrentTileIndex{0}
	, m_IsMoving{ false }
	, m_IsFalling{ false }
	, m_MoveSpeed{100.f}
	, m_LastDirection{ EDirection::DownRight }
{
	m_MoveDistance = playfield->GetTileDistance();
	m_MoveDistance.x = std::abs(m_MoveDistance.x);
	m_MoveDistance.y = std::abs(m_MoveDistance.y);

	m_Owner->SetLocation(playfield->GetTilePositionAtIndex(0));
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
	}

	if (!m_pPlayfield->IsInsideTile(destination, m_CurrentTileIndex)) m_IsFalling = true;
	m_DesiredWorldPosition = destination;

	m_IsMoving = true;
	m_LastDirection = direction;
}

void GridMovementComponent::Update(float dt)
{
	if (!m_IsMoving) return;

	FVector2 newLocation = m_Owner->GetLocation();
	FVector2 direction = m_DesiredWorldPosition - newLocation;
	direction.Normalize();
	newLocation += direction * (m_MoveSpeed * dt);
	m_Owner->SetLocation(newLocation);

	if (EqualWithEpsilon(newLocation, m_DesiredWorldPosition, { 0.7f, 0.7f }))
	{
		if (m_IsFalling)
		{
			m_Owner->SetLocation(m_pPlayfield->GetTilePositionAtIndex(0));
			m_IsFalling = false;
		}
		else
		{
			m_Owner->SetLocation(m_DesiredWorldPosition);
			m_ArrivedOnTile = true;
		}
		m_IsMoving = false;
	}
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