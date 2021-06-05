#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

fox::ResourceManager::~ResourceManager()
{
	for (std::pair<const std::string, Texture2D*> texture : m_TextureMap)
	{
		delete texture.second;
	}
}

void fox::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 

	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

fox::Texture2D* fox::ResourceManager::LoadTexture(const std::string& file)
{
	auto it = m_TextureMap.find(file);
	if (it != m_TextureMap.end())
	{
		return it->second;
	}
	
	const std::string fullPath = m_DataPath + file;
	SDL_Texture* texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	
	Texture2D* tex2D = new Texture2D{ texture };
	m_TextureMap.insert(std::pair<std::string, fox::Texture2D*>(file, tex2D));
	return m_TextureMap[file];
}

fox::Font* fox::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return new Font{ m_DataPath + file, size };
}