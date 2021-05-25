#include "MiniginPCH.h"
#include "GridMovementComponent.h"

#include"GameObject.h"
#include "MathHelper.h"
#include "PlayFieldComponent.h"

GridMovementComponent::GridMovementComponent(fox::GameObject* owner, PlayFieldComponent* playfield)
	: IComponent{ owner }
	, m_pPlayfield{ playfield }
	, m_CurrentRow{}
	, m_CurrentTileIndex{}
	, m_DesiredWorldPosition{}
	, m_IsMoving{ false }
	, m_MoveSpeed{200.f}
	, m_LastDirection{ EDirection::DownRight }
{
}

void GridMovementComponent::Move(EDirection direction)
{
	if (m_IsMoving) return;

	int newIndex{};
	int newRow{};

	//Calculate new index
	switch (m_LastDirection)
	{
	case EDirection::DownLeft:
		newIndex = m_CurrentTileIndex + m_CurrentRow;
		newRow = ++m_CurrentRow;
		break;
	case EDirection::DownRight:
		newIndex = m_CurrentTileIndex + m_CurrentRow + 1;
		newRow = ++newRow;
		break;
	case EDirection::UpLeft:
		newIndex = m_CurrentTileIndex - m_CurrentRow - 1;
		newRow = m_CurrentRow - (m_CurrentTileIndex - newIndex) % (1 + m_CurrentRow);
		break;
	case EDirection::UpRight:
		newIndex = m_CurrentTileIndex - m_CurrentRow;
		newRow = m_CurrentRow - (m_CurrentTileIndex - newIndex) % (1 + m_CurrentRow);
		break;
	}

	//TODO: falling off
	if (newIndex < 0) return; //falling off up
	if (newIndex >= m_pPlayfield->GetTileNr()) return; // falling off down
	if (std::abs(m_CurrentTileIndex - newIndex) < m_CurrentRow) return; // falling off up left

	m_DesiredWorldPosition = m_pPlayfield->GetTilePositionAtIndex(newIndex);
	m_IsMoving = true;
	m_LastDirection = direction;
}

void GridMovementComponent::Update(float dt)
{
	if (!m_IsMoving) return;
	
	FVector2 newLocation = m_Owner->GetLocation();
	FVector2 direction = m_DesiredWorldPosition - newLocation;
	direction.Normalize();
	newLocation += direction * m_MoveSpeed;
	newLocation *= dt;
	m_Owner->SetLocation(newLocation);

	if (EqualWithEpsilon(newLocation, m_DesiredWorldPosition, {0.1f, 0.1f})) m_IsMoving = false;
}

void GridMovementComponent::SetSpeed(float speed)
{
	m_MoveSpeed = speed;
}

EDirection GridMovementComponent::GetDirection() const
{
	return m_LastDirection;
}