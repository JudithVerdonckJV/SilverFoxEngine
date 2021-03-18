#include "MiniginPCH.h"
#include "Transform.h"

fox::Transform::Transform()
	: IComponent { nullptr }
	, m_Position{}
	, m_Rotation{}
	, m_Scale{1.f, 1.f}
{
}


void fox::Transform::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void fox::Transform::SetPosition(const FVector2& position)
{
	m_Position = position;
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