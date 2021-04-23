#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "GameObject.h"
#include "Texture2D.h"

#include "ResourceManager.h"
#include "Renderer.h"

fox::TextureComponent::TextureComponent(GameObject* owner)
	: IComponent{ owner }
	, m_pTexture{ nullptr }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture("fox.png");
}

fox::TextureComponent::~TextureComponent()
{
	delete m_pTexture;
}

void fox::TextureComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_Owner->GetLocation().x, m_Owner->GetLocation().y);
}

void fox::TextureComponent::SetTexture(const std::string& texturePath)
{
	delete m_pTexture;
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
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