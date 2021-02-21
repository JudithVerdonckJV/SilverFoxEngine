#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

fox::GameObject::GameObject()
	: m_pComponents{}
	, m_pTransform{ }
{
	Transform* transform{ new Transform };
	AddComponent(transform);
	m_pTransform = transform; // direct access, no casting needed
}

fox::GameObject::~GameObject()
{
	for (IComponent* comp : m_pComponents)
	{
		delete comp;
	}
}

void fox::GameObject::Render() const
{
	for (IComponent* comp : m_pComponents)
	{
		comp->Render(m_pTransform->Position());
	}
}

void fox::GameObject::Update(float deltaTime)
{
	for (IComponent* comp : m_pComponents)
	{
		comp->Update(deltaTime);
	}
}

void fox::GameObject::FixedUpdate(float tick)
{
	for (IComponent* comp : m_pComponents)
	{
		comp->FixedUpdate(tick);
	}
}

void fox::GameObject::LateUpdate(float deltaTime)
{
	for (IComponent* comp : m_pComponents)
	{
		comp->LateUpdate(deltaTime);
	}
}

void fox::GameObject::AddComponent(IComponent* const newComponent)
{
	for (IComponent* component : m_pComponents)
	{
		if (component->Id() == newComponent->Id())
		{
			delete newComponent;
			throw "Component already attached to this gameobject!";
			return;
		}	
	}

	m_pComponents.push_back(newComponent);
}