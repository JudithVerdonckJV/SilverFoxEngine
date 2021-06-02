#pragma once
#include "utils.h"

namespace fox
{
	class GameObject;

	class GameStatics
	{
	public:
		static FVector2 WINDOW_SIZE;
		static void AddPlayer(GameObject* player);
		static GameObject* GetPlayerObject(size_t index);

	private:
		static std::vector<GameObject*> m_Players;
	};
}
