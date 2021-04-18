#include "MiniginPCH.h"
#include "Transform.h"

fox::Transform::Transform(GameObject* owner)
	: IComponent { owner }
	, m_Location{}
	, m_Rotation{}
	, m_Scale{1.f, 1.f}
{
}

fox::Transform::Transform(const FVector2& location, const FVector2& rotation, const FVector2& scale)
	:IComponent{ nullptr }
	, m_Location{ location }
	, m_Rotation{ rotation }
	, m_Scale{ scale }
{
}

void fox::Transform::SetLocation(const float x, const float y)
{
	m_Location.x = x;
	m_Location.y = y;
}

void fox::Transform::SetLocation(const FVector2& position)
{
	m_Location = position;
}

void fox::Transform::SetRotation(float x, float y)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
}

void fox::Transform::SetRotation(const FVector2& rotation)
{
	m_Rotation = rotation;
}

void fox::Transform::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void fox::Transform::SetScale(const FVector2& scale)
{
	m_Scale = scale;
}