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
		virtual void EnterScene() {};
		virtual void ExitScene() {};

		virtual void Update(float ) {};
		virtual void FixedUpdate(float ) {};
		virtual void LateUpdate(float ) {};
		virtual void Render() const {};

		void RootEnterScene();
		void RootExitScene();
		
		void RootUpdate(float );
		void RootFixedUpdate(float );
		void RootLateUpdate(float );

		void RootRender() const;

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
