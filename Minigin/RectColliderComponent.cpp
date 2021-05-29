#include "MiniginPCH.h"
#include "RectColliderComponent.h"
#include <SDL.h>
#include "Renderer.h"

#include "GameObject.h"
#include "ColliderManager.h"

using namespace fox;

RectColliderComponent::RectColliderComponent(GameObject* owner, FVector2 position, FVector2 widhtHeight)
	: IComponent{ owner }
	, m_DrawDebug{ false }
	, m_RelativeLocation{ position }
	, m_WorldLocation{}
	, m_Dimensions{ widhtHeight }
	, m_Id{}
{
	ColliderManager::GetInstance().RegisterColliderComponent(this);
}

RectColliderComponent::RectColliderComponent(GameObject* owner, FVector2 position, float width, float height)
	: RectColliderComponent{owner, position, {width, height}}
{

}

RectColliderComponent::RectColliderComponent(GameObject* owner, float x, float y, float width, float height)
	: RectColliderComponent{owner, {x, y}, {width, height}}
{
}

RectColliderComponent::RectColliderComponent(GameObject* owner, float width, float height)
	: RectColliderComponent{ owner, {}, {width, height}}
{
}

RectColliderComponent::RectColliderComponent(GameObject* owner)
	: RectColliderComponent{ owner, {}, {} }
{
}

void RectColliderComponent::Render() const
{
	if (!m_DrawDebug) return;

	//draw collider
	SDL_Renderer* renderer{Renderer::GetInstance().GetSDLRenderer()};

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLineF(renderer, m_WorldLocation.x, m_WorldLocation.y, m_WorldLocation.x + m_Dimensions.x, m_WorldLocation.y);
	SDL_RenderDrawLineF(renderer, m_WorldLocation.x + m_Dimensions.x, m_WorldLocation.y, m_WorldLocation.x + m_Dimensions.x, m_WorldLocation.y + m_Dimensions.y);
	SDL_RenderDrawLineF(renderer, m_WorldLocation.x + m_Dimensions.x, m_WorldLocation.y + m_Dimensions.y, m_WorldLocation.x, m_WorldLocation.y + m_Dimensions.y);
	SDL_RenderDrawLineF(renderer, m_WorldLocation.x, m_WorldLocation.y + m_Dimensions.y, m_WorldLocation.x, m_WorldLocation.y);
}

void RectColliderComponent::Update(float)
{
	m_WorldLocation = m_Owner->GetLocation();
	m_WorldLocation -= m_RelativeLocation;
}

void RectColliderComponent::FixedUpdate(float)
{
	ColliderManager::GetInstance().TriggerOverlapEventsFromComponent(m_Id);
}

void RectColliderComponent::OnOverlap(GameObject* other)
{
	m_OverlapCallback(other);
}

void RectColliderComponent::SetOverlapCallback(std::function<void(GameObject*)> callback)
{
	m_OverlapCallback = callback;
}

FVector2 RectColliderComponent::GetDimensions() const
{
	return m_Dimensions;
}

float RectColliderComponent::GetWidth() const
{
	return m_Dimensions.x;
}

float RectColliderComponent::GetHeight() const
{
	return m_Dimensions.y;
}

FVector2 RectColliderComponent::GetRelativePosition() const
{
	return m_RelativeLocation;
}

float RectColliderComponent::GetRelativeX() const
{
	return m_RelativeLocation.x;
}

float RectColliderComponent::GetRelativeY() const
{
	return m_RelativeLocation.y;
}

FVector2 RectColliderComponent::GetWorldLocation() const
{
	return m_WorldLocation;
}

void RectColliderComponent::SetDimensions(FVector2 dimensions)
{
	m_Dimensions = dimensions;
}

void RectColliderComponent::SetDimensions(float width, float height)
{
	m_Dimensions = { width, height };
}

void RectColliderComponent::SetWidth(float width)
{
	m_Dimensions.x = width;
}

void RectColliderComponent::SetHeight(float height)
{
	m_Dimensions.y = height;
}

void RectColliderComponent::SetRelativePosition(FVector2 position)
{
	m_RelativeLocation = position;
}

void RectColliderComponent::SetRelativePosition(float x, float y)
{
	m_RelativeLocation = { x, y };
}

void RectColliderComponent::SetRelativeX(float x)
{
	m_RelativeLocation.x = x;
}

void RectColliderComponent::SetRelativeY(float y)
{
	m_RelativeLocation.y = y;
}

void RectColliderComponent::DrawDebug(bool drawDebug)
{
	m_DrawDebug = drawDebug;
}