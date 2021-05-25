#pragma once
#include "utils.h"

namespace fox
{
	class GameObject;

	class GameStatics
	{
	public:
		static FVector2 WINDOW_SIZE;
		static GameObject* GetPlayerObject(size_t index);

	private:
		friend class InputManager;
		static std::vector<GameObject*> m_Players;
	};
}
