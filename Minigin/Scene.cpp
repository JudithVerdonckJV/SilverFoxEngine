#include "MiniginPCH.h"
#include "Scene.h"
#include "IComponent.h"


fox::Scene::Scene()
{

}

fox::Scene::~Scene()
{
	for (GameObject* object : m_Objects)
	{
		delete object;
	}
}

void fox::Scene::AddObject(GameObject* const object)
{
	m_Objects.push_back(object);
}

void fox::Scene::RootUpdate(float deltaTime)
{
	Update(deltaTime);
	
	for(GameObject* const object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void fox::Scene::RootFixedUpdate(float tick)
{
	FixedUpdate(tick);

	for (GameObject* const object : m_Objects)
	{
		object->FixedUpdate(tick);
	}
}

void fox::Scene::RootLateUpdate(float deltaTime)
{
	LateUpdate(deltaTime);
	
	for (GameObject* const object : m_Objects)
	{
		object->LateUpdate(deltaTime);
	}
}

void fox::Scene::RootRender() const
{
	Render();
	
	for (const GameObject* const object : m_Objects)
	{
		object->Render();
	}
}