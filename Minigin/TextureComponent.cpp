#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "MathHelper.h"

#include "GameObject.h"
#include "Texture2D.h"

#include "ResourceManager.h"
#include "Renderer.h"

fox::TextureComponent::TextureComponent(GameObject* owner)
	: IComponent{ owner }
	, m_pTexture{ nullptr }
{
}

fox::TextureComponent::TextureComponent(GameObject* owner, const std::string& path)
	:IComponent{owner}
	, m_pTexture{ nullptr }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
}

fox::TextureComponent::~TextureComponent()
{
	delete m_pTexture;
}

void fox::TextureComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_WorldLocation.x, m_WorldLocation.y);
}

void fox::TextureComponent::Update(float)
{
	m_WorldLocation = m_Owner->GetLocation();
	m_WorldLocation.x -= m_Pivot.x * GetWidth();
	m_WorldLocation.y -= m_Pivot.y * GetHeight();
}

void fox::TextureComponent::SetTexture(const std::string& texturePath)
{
	delete m_pTexture;
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

void fox::TextureComponent::SetPivot(float x, float y)
{
	m_Pivot.x = x;
	m_Pivot.y = y;
}

void fox::TextureComponent::SetPivot(FVector2 xy)
{
	SetPivot(xy.x, xy.y);
}

FVector2 fox::TextureComponent::GetDimensions() const
{
	return m_pTexture->GetDimensions();
}

float fox::TextureComponent::GetWidth() const
{
	return m_pTexture->GetDimensions().x;
}

float fox::TextureComponent::GetHeight() const
{
	return m_pTexture->GetDimensions().y;
}

FVector2 fox::TextureComponent::GetWorldLocation() const
{
	return m_WorldLocation;
}