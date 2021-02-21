#pragma once
#include "SceneManager.h"

namespace fox
{
	class GameObject;
	class Scene final
	{
		friend void SceneManager::AddScene(const std::string& name); // constructor is private; only manager can access it
	
	public:
		void AddObject(GameObject* const object);

		void Update(float deltaTime);
		void Render() const;

		~Scene();

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene();

		std::vector <GameObject*> m_Objects{};
	};

}
