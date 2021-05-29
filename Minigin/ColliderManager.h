#pragma once
#include "Singleton.h"

namespace fox
{
	class RectColliderComponent;

	class ColliderManager : public fox::Singleton<ColliderManager>
	{
	public:
		~ColliderManager() = default;

		void TriggerOverlapEventsFromComponent(int id);

	private:
		std::vector<RectColliderComponent*> m_pColliders;

		bool IsOverlapping(int id, int i);
		
		friend class RectColliderComponent;
		int RegisterColliderComponent(RectColliderComponent* collider);
		
		friend class Singleton<ColliderManager>;
		ColliderManager();
	};
}