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
		virtual ~SceneManager();
		
		void AddScene(const std::string& name);

		void Update(float deltaTime);
		void FixedUpdate(float ticked);
		void LateUpdate(float deltaTime);

		void Render();

		void SetActiveScene(const std::string& name);
		void AddObjectToScene(const std::string& name, GameObject* newObject);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::unordered_map<std::string, Scene*> m_pScenesMap{};
		std::string m_ActiveScene{};
	};
}
