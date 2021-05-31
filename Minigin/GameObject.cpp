#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "Transform.h"
#include "SubjectComponent.h"
#include "InputComponent.h"
#include "Scene.h"

fox::GameObject::GameObject(GameObject* owner)
	: m_Owner{owner}
	, m_pComponents{ }
	, m_pChildObjects{ }
	, m_pTransform{ nullptr }
	, m_pSubject{ nullptr }
	, m_UserComponent{}
	, m_Tag{ "" }
	, m_IsActive{ true }
	, m_IsVisible{ true }
{
	if (owner != nullptr) owner->AddChild(this); //set owner to another object
	
	m_pTransform = new Transform{ this };
}

fox::GameObject::GameObject(Scene* owner)
	: m_Owner{ nullptr }
	, m_pComponents{ }
	, m_pChildObjects{ }
	, m_pTransform{ nullptr }
	, m_pSubject{ nullptr }
	, m_UserComponent{}
	, m_Tag{ "" }
	, m_IsActive{ true }
	, m_IsVisible{ true }
{
	owner->AddObject(this); // adding this to scene

	m_pTransform = new Transform{ this };
}

fox::GameObject::~GameObject()
{
	for (IComponent* comp : m_pComponents)
	{
		delete comp;
	}

	for (GameObject* child : m_pChildObjects)
	{
		delete child;
	}
}

void fox::GameObject::Update(float deltaTime)
{
	if (!m_IsActive) return;
	
	for (IComponent* comp : m_pComponents)
	{
		comp->Update(deltaTime);
	}

	for (GameObject* child : m_pChildObjects)
	{
		child->Update(deltaTime);
	}
}

void fox::GameObject::FixedUpdate(float tick)
{
	if (!m_IsActive) return;

	for (IComponent* comp : m_pComponents)
	{
		comp->FixedUpdate(tick);
	}

	for (GameObject* child : m_pChildObjects)
	{
		child->FixedUpdate(tick);
	}
}

void fox::GameObject::LateUpdate(float deltaTime)
{
	if (!m_IsActive) return;
	
	for (IComponent* comp : m_pComponents)
	{
		comp->LateUpdate(deltaTime);
	}

	for (GameObject* child : m_pChildObjects)
	{
		child->LateUpdate(deltaTime);
	}
}

void fox::GameObject::Render() const
{
	if (!m_IsVisible) return;
	
	for (IComponent* comp : m_pComponents)
	{
		comp->Render();
	}

	for (GameObject* child : m_pChildObjects)
	{
		child->Render();
	}
}

void fox::GameObject::SetTransform(const FVector2& position, const FVector2& rotation, const FVector2& scale)
{
	m_pTransform->SetLocation(position);
	m_pTransform->SetRotation(rotation);
	m_pTransform->SetScale(scale);
}

fox::Transform* fox::GameObject::GetTransform() const
{ 
	return m_pTransform;
}

void fox::GameObject::SetLocation(float x, float y)
{
	m_pTransform->SetLocation(x, y);
}

void fox::GameObject::SetLocation(const FVector2& xy)
{
	m_pTransform->SetLocation(xy);
}

FVector2 fox::GameObject::GetLocation() const
{ 
	return m_pTransform->Location();
}

const fox::SubjectComponent* fox::GameObject::GetSubject() const
{
	return m_pSubject;
}

fox::IComponent* fox::GameObject::GetUserComponent() const
{
	return m_UserComponent;
}

void fox::GameObject::SetUserComponent(IComponent* component)
{
	m_UserComponent = component;
}

void fox::GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

const std::string& fox::GameObject::GetTag() const
{
	return m_Tag;
}

fox::GameObject* fox::GameObject::GetChildByTag(const std::string& tag) const
{
	for (GameObject* child : m_pChildObjects)
	{
		if (child->GetTag() == tag) return child;
	}

	return nullptr;
}

fox::GameObject* fox::GameObject::GetChildByIndex(size_t index) const
{
	if (index >= m_pChildObjects.size()) return nullptr;
	
	return m_pChildObjects[index];
}

void fox::GameObject::AddComponent(IComponent* const newComponent)
{
	if (dynamic_cast<SubjectComponent*>(newComponent)) m_pSubject = static_cast<SubjectComponent*>(newComponent);

	//TODO: only one component of each kind?
	m_pComponents.push_back(newComponent);
}

void fox::GameObject::AddChild(GameObject* const childObject)
{
	m_pChildObjects.push_back(childObject);
}

void fox::GameObject::SetActive(bool active)
{
	m_IsActive = active;
}

void fox::GameObject::SetVisibility(bool visible)
{
	m_IsVisible = visible;
}

bool fox::GameObject::IsActive() const
{
	return m_IsActive;
}

bool fox::GameObject::IsVisible() const
{
	return m_IsVisible;
}