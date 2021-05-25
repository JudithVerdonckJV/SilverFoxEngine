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
	m_pTexture = ResourceManager::GetInstance().LoadTexture("fox.png");
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
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_RelativeLocation.x, m_RelativeLocation.y);
}

void fox::TextureComponent::Update(float)
{
	m_RelativeLocation = m_Owner->GetLocation();
	m_RelativeLocation.x -= m_Pivot.x * GetWidth();
	m_RelativeLocation.y -= m_Pivot.y * GetHeight();
	//scaling?
}

void fox::TextureComponent::SetTexture(const std::string& texturePath)
{
	delete m_pTexture;
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

void fox::TextureComponent::SetPivot(float x, float y)
{
	m_Pivot.x = Clamp(x, 0.f, 1.f);
	m_Pivot.y = Clamp(y, 0.f, 1.f);	
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