#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include <SDL.h>
#include <SDL_ttf.h>

#include "IComponent.h"
#include "Font.h"
#include "Texture2D.h"

namespace fox
{
	class FontRender final : public IComponent
	{
	public:
		FontRender() = default;
		FontRender(const std::string& fontPath, const std::string& text);
		virtual ~FontRender();

		virtual void Render(const FVector2& worldPos) const override;

		void SetFont(const std::string & fontPath, int size);
		void SetText(const std::string& text);
		void SetColor(float r, float g, float b);

		void SetLocalPos(const FVector2& localPos);
		void SetLocalPos(float x, float y);

	private:
		Font* m_pFont;
		std::string m_Text;
		Texture2D* m_pTexture;
		SDL_Color m_Color;

		FVector2 m_LocalPos;

		void CreateTexture();
	};
}


