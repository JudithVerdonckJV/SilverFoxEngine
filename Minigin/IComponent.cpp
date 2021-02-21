#include "MiniginPCH.h"
#include "IComponent.h"

fox::IComponent::ComponentID fox::IComponent::Id() const
{
	return m_Id;
}