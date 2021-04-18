#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace fox
{
	class GameObject;
	class Scene 
	{		
		template <typename T>
		friend void SceneManager::AddScene<T>(const std::string& name);
	
	public:
		virtual ~Scene();
		
		virtual void LoadScene() {};
		
		void Update(float deltaTime);
		void FixedUpdate(float tick);
		void LateUpdate(float deltaTime);

		void Render() const;

	protected:
		
		explicit Scene();
	
	private:
		friend class GameObject;
		void AddObject(GameObject* const object);

		std::vector <GameObject*> m_Objects{};

	public:
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	};
}
