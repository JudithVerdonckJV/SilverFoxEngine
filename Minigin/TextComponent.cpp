#include "MiniginPCH.h"
#include "TextComponent.h"

#include <SDL_ttf.h>

#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

#include "Renderer.h"
#include "ResourceManager.h"

fox::TextComponent::TextComponent(GameObject* owner)
	:IComponent{ owner }
	, m_pFont{ nullptr }
	, m_FontPath{ "Lingua.otf" }
	, m_Size{ 24 }
	, m_pTexture{ nullptr }
	, m_Color{ 255, 255, 255, 255 }
	, m_Text{ "Lorem Ipsum" }
{
	CreateTexture();
}

fox::TextComponent::~TextComponent()
{
	delete m_pTexture;
	delete m_pFont;
}

void fox::TextComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_Owner->GetLocation().x, m_Owner->GetLocation().y );
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
	delete m_pFont;
	m_pFont = ResourceManager::GetInstance().LoadFont(m_FontPath, m_Size);
	if (m_pFont == nullptr) throw "Font not initialized";
	
	SDL_Surface* surface = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
	if (surface == nullptr) throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);
	if (texture == nullptr) throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

	SDL_FreeSurface(surface);
	m_pTexture = new Texture2D{ texture };
}