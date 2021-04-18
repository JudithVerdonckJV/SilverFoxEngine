#include "MiniginPCH.h"
#include "IComponent.h"
#include "GameObject.h"

fox::IComponent::IComponent(GameObject* owner)
	:m_Owner{ owner }
{
	owner->AddComponent(this);
}