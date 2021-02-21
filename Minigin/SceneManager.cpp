#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

fox::SceneManager::~SceneManager()
{
	for (std::pair<const std::string, Scene*>& scene : m_pScenesMap)
	{
		delete scene.second;
	}
}

void fox::SceneManager::AddScene(const std::string& name)
{
	if (m_pScenesMap.size() == 0) m_ActiveScene = name;
	
	Scene* scene{ new Scene{} };
	m_pScenesMap.insert(std::pair<std::string, Scene*>{name, scene});
}

void fox::SceneManager::Update(float deltaTime)
{
	m_pScenesMap[m_ActiveScene]->Update(deltaTime);
}

void fox::SceneManager::FixedUpdate(float tick)
{
	m_pScenesMap[m_ActiveScene]->FixedUpdate(tick);
}

void fox::SceneManager::LateUpdate(float deltaTime)
{
	m_pScenesMap[m_ActiveScene]->LateUpdate(deltaTime);
}

void fox::SceneManager::Render()
{
	m_pScenesMap[m_ActiveScene]->Render();
}

void fox::SceneManager::SetActiveScene(const std::string& name)
{
	const auto it{ m_pScenesMap.find(name) };

	if (it != m_pScenesMap.end()) m_ActiveScene = name;
	else throw "SceneManager, SetActiveScene: Scene does not exist!";
}

void fox::SceneManager::AddObjectToScene(const std::string& name, GameObject* newObject)
{
	const auto it{ m_pScenesMap.find(name) };

	if (it != m_pScenesMap.end()) m_pScenesMap[name]->AddObject(newObject);
	else throw "SceneManager, AddObjectToScene: Scene does not exist!";
}