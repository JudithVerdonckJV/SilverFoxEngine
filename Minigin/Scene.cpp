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

void fox::Scene::Update(float deltaTime)
{
	for(GameObject* const object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void fox::Scene::FixedUpdate(float tick)
{
	for (GameObject* const object : m_Objects)
	{
		object->FixedUpdate(tick);
	}
}

void fox::Scene::LateUpdate(float deltaTime)
{
	for (GameObject* const object : m_Objects)
	{
		object->LateUpdate(deltaTime);
	}
}

void fox::Scene::Render() const
{
	for (const GameObject* const object : m_Objects)
	{
		object->Render();
	}
}