#include "MiniginPCH.h"
#include "GridMovementComponent.h"

#include"GameObject.h"
#include "PlayFieldComponent.h"

GridMovementComponent::GridMovementComponent(fox::GameObject* owner, PlayFieldComponent* playfield)
	: IComponent{ owner }
	, m_Playfield{ playfield }
	, m_CurrentGridPosition{}
	, m_DesiredGridPosition{}
	, m_IsMoving{ false }
{
}

void GridMovementComponent::Move(EDirection direction)
{
	if (m_IsMoving) return;

	//do "search new location" math

	m_DesiredGridPosition = {}; // hook up new grid location
	m_IsMoving = true;
}

void GridMovementComponent::Update(float deltaTime)
{
	if (!m_IsMoving) return;
	//move to desired location

	//if (currentWorld == desired) m_IsMoving = false;
}