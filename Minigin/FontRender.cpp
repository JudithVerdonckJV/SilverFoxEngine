#include "MiniginPCH.h"


#include "FontRender.h"
#include "ResourceManager.h"
#include "Renderer.h"


fox::FontRender::FontRender(const std::string& fontPath, const std::string& text)
	: m_LocalPos{}
	, m_Text{ text }
	, m_pTexture{ nullptr }
	, m_pFont{ nullptr }
	, m_Color{255, 255, 255, 255}
{
	SetFont(fontPath, 36);
}

fox::FontRender::~FontRender()
{
	delete m_pTexture;
	delete m_pFont;
}

void fox::FontRender::Render(const FVector2& worldPos) const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, worldPos.x + m_LocalPos.x, worldPos.y + m_LocalPos.y);
}

void fox::FontRender::SetFont(const std::string& textPath, int size)
{
	delete m_pFont;
	m_pFont = ResourceManager::GetInstance().LoadFont(textPath, size);
	if (m_pFont == nullptr) throw "Font not initialized";

	CreateTexture();
}

void fox::FontRender::SetText(const std::string& text)
{
	m_Text = text;
	CreateTexture();
}

void fox::FontRender::SetColor(float r, float g, float b)
{
	m_Color = { Uint8(r * 255), Uint8(g * 255), Uint8(b * 255) };
}

void fox::FontRender::SetLocalPos(const FVector2& localPos)
{
	m_LocalPos = localPos;
}

void fox::FontRender::SetLocalPos(float x, float y)
{
	m_LocalPos = { x, y };
}

void fox::FontRender::CreateTexture()
{
	SDL_Surface* surface = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
	if (surface == nullptr) throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);
	if (texture == nullptr) throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

	SDL_FreeSurface(surface);
	m_pTexture = new Texture2D{ texture };
}