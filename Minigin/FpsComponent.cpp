#include "MiniginPCH.h"
#include "FpsComponent.h"

#include "SDL_ttf.h"

#include "GameObject.h"
#include "Font.h"
#include "Texture2D.h"

#include "ResourceManager.h"
#include "Renderer.h"

fox::FpsComponent::FpsComponent(GameObject* owner)
	: IComponent{ owner }
	, m_pFont{ nullptr }
	, m_FontPath{ "Lingua.otf" }
	, m_Size{ 24 }
	, m_pTexture{ nullptr }
	, m_Color{ 255, 255, 255, 255 }
	, m_Text{ "00.00" }
{
	CreateTexture();
}

fox::FpsComponent::~FpsComponent()
{
	delete m_pFont;
	delete m_pTexture;
}

void fox::FpsComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_Owner->GetLocation().x, m_Owner->GetLocation().y);
}

void fox::FpsComponent::Update(float deltaTime)
{
	m_Text = std::to_string(1.f / deltaTime);
	CreateTexture();
}

void fox::FpsComponent::SetFont(const std::string& fontPath)
{
	m_FontPath = fontPath;
}

void fox::FpsComponent::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	m_Color = { r, g, b, a };
}

void fox::FpsComponent::SetSize(int size)
{
	m_Size = size;
}

void fox::FpsComponent::CreateTexture()
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