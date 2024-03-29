#include "MiniginPCH.h"
#include "TextComponent.h"

#include <SDL_ttf.h>

#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

#include "Renderer.h"
#include "ResourceManager.h"

fox::TextComponent::TextComponent(GameObject* owner, FVector2 position)
	:IComponent{ owner }
	, m_pFont{ nullptr }
	, m_FontPath{ "Lingua.otf" }
	, m_Size{ 24 }
	, m_pTexture{ nullptr }
	, m_Color{ 255, 255, 255, 255 }
	, m_Text{ "Lorem Ipsum" }
	, m_WorldLocation{}
	, m_RelativeLocation{ position }
{
	CreateTexture();
}

fox::TextComponent::~TextComponent()
{
	delete m_pTexture;
	delete m_pFont;
}

void fox::TextComponent::Update(float)
{
	m_WorldLocation = m_Owner->GetLocation();
	m_WorldLocation -= m_RelativeLocation;
}

void fox::TextComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_WorldLocation.x, m_WorldLocation.y );
}

void fox::TextComponent::SetFont(const std::string& fontPath)
{
	m_FontPath = fontPath;
	CreateTexture();
}

void fox::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	CreateTexture();
}

void fox::TextComponent::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	m_Color = { r, g, b, a };
	CreateTexture();
}

void fox::TextComponent::SetSize(int size)
{
	m_Size = size;
	CreateTexture();
}

void fox::TextComponent::CreateTexture()
{
	if (m_pFont) delete m_pFont;
	if (m_pTexture) delete m_pTexture;
	
	m_pFont = ResourceManager::GetInstance().LoadFont(m_FontPath, m_Size);
	
	SDL_Surface* surface = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);

	m_pTexture = new Texture2D{ texture };
	
	SDL_FreeSurface(surface);
}