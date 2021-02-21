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
