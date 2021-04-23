#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

fox::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* fox::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

fox::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_pTexture = texture;
}

FVector2 fox::Texture2D::GetDimensions() const
{
	int width{};
	int height{};
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &width, &height);

	return FVector2{ (float)width, (float)height };
}