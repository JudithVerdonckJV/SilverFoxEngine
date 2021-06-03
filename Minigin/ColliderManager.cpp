#include "MiniginPCH.h"
#include "ColliderManager.h"

#include "GameObject.h"

#include "RectColliderComponent.h"

using namespace fox;

ColliderManager::ColliderManager()
	: m_pColliders{}
{
}

int ColliderManager::RegisterColliderComponent(RectColliderComponent* collider)
{
	m_pColliders.push_back(collider);
	return (int)m_pColliders.size() - 1;
}

void ColliderManager::TriggerOverlapEventsFromComponent(int id)
{
	for (int i{}; i < (int)m_pColliders.size(); ++i)
	{
		if (i == id) continue;
		if (!m_pColliders[i]->GetOwner()->IsActive()) continue;

		if (IsOverlapping(id, i) || IsOverlapping(i, id))
		{
			m_pColliders[i]->OnOverlap(m_pColliders[id]->GetOwner());
		}
	}
}

bool ColliderManager::IsOverlapping(int id, int i)
{
	FVector2 location_ID{ m_pColliders[id]->GetWorldLocation() };
	FVector2 dimensions_ID{ m_pColliders[id]->GetDimensions() };

	FVector2 location_I{ m_pColliders[i]->GetWorldLocation() };
	FVector2 dimensions_I{ m_pColliders[i]->GetDimensions() };

	//CHECK LEFTBOTTOM POINT
	if (location_ID.x >= location_I.x && location_ID.x <= location_I.x + dimensions_I.x &&
		location_ID.y >= location_I.y && location_ID.y <= location_I.y + dimensions_I.y)
		return true;

	//CHECK RIGHTBOTTOM POINT
	if (location_ID.x + dimensions_ID.x >= location_I.x && location_ID.x + dimensions_ID.x <= location_I.x + dimensions_I.x &&
		location_ID.y >= location_I.y && location_ID.y <= location_I.y + dimensions_I.y)
		return true;

	//CHECK LEFTTOP POINT
	if (location_ID.x >= location_I.x && location_ID.x <= location_I.x + dimensions_I.x &&
		location_ID.y + dimensions_ID.x >= location_I.y && location_ID.y + dimensions_ID.y <= location_I.y + dimensions_I.y)
		return true;

	//CHECK RIGHTTOP POINT
	if (location_ID.x + dimensions_ID.x >= location_I.x && location_ID.x + dimensions_ID.x <= location_I.x + dimensions_I.x &&
		location_ID.y + dimensions_ID.x >= location_I.y && location_ID.y + dimensions_ID.y <= location_I.y + dimensions_I.y)
		return true;

	return false;
}