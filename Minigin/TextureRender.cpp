#include "MiniginPCH.h"
#include "TextureRender.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "IComponent.h"

fox::TextureRender::TextureRender(const std::string& textPath)
	: m_LocalPos{}
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(textPath);
}

fox::TextureRender::~TextureRender()
{
	delete m_pTexture;
}

void fox::TextureRender::Render(const FVector2& worldPos) const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, worldPos.x + m_LocalPos.x, worldPos.y + m_LocalPos.y);
}

void fox::TextureRender::SetTexture(const std::string& textPath)
{
	delete m_pTexture;
	m_pTexture = ResourceManager::GetInstance().LoadTexture(textPath);
}

void fox::TextureRender::SetLocalPos(const FVector2& localPos)
{
	m_LocalPos = localPos;
}

void fox::TextureRender::SetLocalPos(float x, float y)
{
	m_LocalPos = { x, y };
}