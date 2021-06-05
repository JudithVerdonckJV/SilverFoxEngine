#pragma once
#include <map>
#include <string>
#include "Singleton.h"

namespace fox
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		~ResourceManager();
		Texture2D* LoadTexture(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size) const;

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

		std::string m_DataPath;

		std::map<const std::string, Texture2D*> m_TextureMap{};
	};
}
