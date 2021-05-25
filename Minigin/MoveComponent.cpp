#include "MiniginPCH.h"
#include "MoveComponent.h"

#include "GameObject.h"

fox::MoveComponent::MoveComponent(GameObject* owner)
	:IComponent{owner}
{
}

void fox::MoveComponent::AddMovementInput(float x, float y)
{
	FVector2 newLocation = m_Owner->GetLocation();
	newLocation.x += x;
	newLocation.y += y;
	m_Owner->SetLocation(newLocation);
}

void fox::MoveComponent::AddMovementInput(const FVector2& distance)
{
	AddMovementInput(distance.x, distance.y);
}