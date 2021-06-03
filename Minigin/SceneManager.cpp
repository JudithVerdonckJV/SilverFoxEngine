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

void fox::SceneManager::Update(float deltaTime)
{
	m_pScenesMap[m_ActiveScene]->RootUpdate(deltaTime);
}

void fox::SceneManager::FixedUpdate(float tick)
{
	m_pScenesMap[m_ActiveScene]->RootFixedUpdate(tick);
}

void fox::SceneManager::LateUpdate(float deltaTime)
{
	m_pScenesMap[m_ActiveScene]->RootLateUpdate(deltaTime);
}

void fox::SceneManager::Render()
{
	m_pScenesMap[m_ActiveScene]->RootRender();
}

void fox::SceneManager::SetActiveScene(const std::string& name)
{
	m_pScenesMap[m_ActiveScene]->RootExitScene();
	
	const auto it{ m_pScenesMap.find(name) };

	if (it != m_pScenesMap.end()) m_ActiveScene = name;
	else throw "SceneManager, SetActiveScene: Scene does not exist!";

	m_pScenesMap[m_ActiveScene]->RootEnterScene();
}