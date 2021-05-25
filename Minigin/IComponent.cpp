#include "MiniginPCH.h"
#include "IComponent.h"
#include "GameObject.h"

fox::IComponent::IComponent(GameObject* owner)
	:m_Owner{ owner }
{
	owner->AddComponent(this);
}

fox::GameObject* fox::IComponent::GetOwner() const
{
	return m_Owner;
}