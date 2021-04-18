#pragma once
#include "Singleton.h"
#include <unordered_map>

namespace fox
{
	class Scene;
	class GameObject;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();
		
		template <typename T>
		void AddScene(const std::string& name)
		{
			if (m_pScenesMap.size() == 0) m_ActiveScene = name;

			Scene* scene{ new T{} };
			scene->LoadScene();
			m_pScenesMap.insert(std::pair<std::string, Scene*>{name, scene});
		}

		void Update(float deltaTime);
		void FixedUpdate(float ticked);
		void LateUpdate(float deltaTime);

		void Render();

		void SetActiveScene(const std::string& name);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::unordered_map<std::string, Scene*> m_pScenesMap{};
		std::string m_ActiveScene{};
	};
}
