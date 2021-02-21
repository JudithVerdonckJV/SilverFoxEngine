#include "MiniginPCH.h"


#include "FPS.h"
#include "ResourceManager.h"
#include "Renderer.h"

fox::FPS::FPS(const std::string& fontPath)
	: m_LocalPos{}
	, m_pFont{}
	, m_pTexture{}
	, m_Text{ "0.000" }
	, m_Color{255, 255, 255, 255}
{
	m_Id = fox::IComponent::ComponentID::FPS;
	SetFont(fontPath, 36);
}

fox::FPS::~FPS()
{
	delete m_pTexture;
	delete m_pFont;
}

void fox::FPS::Render(const FVector2& worldPos) const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, worldPos.x + m_LocalPos.x, worldPos.y + m_LocalPos.y);
}

void fox::FPS::Update(float deltaTime)
{
	m_Text = std::to_string(1.f / deltaTime);

	CreateTexture();
}

void fox::FPS::SetLocalPos(const FVector2& localPos)
{
	m_LocalPos = localPos;
}

void fox::FPS::SetLocalPos(float x, float y)
{
	m_LocalPos = { x, y };
}

void fox::FPS::SetColor(float r, float g, float b)
{
	m_Color = { Uint8(r * 255), Uint8(g * 255), Uint8(b * 255) };
}

void fox::FPS::SetFont(const std::string& fontPath, int size)
{
	m_pFont = ResourceManager::GetInstance().LoadFont(fontPath, size);
	if (m_pFont == nullptr) throw "Font not initialized";
	CreateTexture();
}

void fox::FPS::CreateTexture()
{
	SDL_Surface* surface = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
	if (surface == nullptr) throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);
	if (texture == nullptr) throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

	SDL_FreeSurface(surface);
	delete m_pTexture;
	m_pTexture = new Texture2D{ texture };
}