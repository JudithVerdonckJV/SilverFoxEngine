#pragma once
#include <SDL.h>
#include "IComponent.h"

#include "utils.h"

namespace fox
{
	class GameObject;
	class Font;
	class Texture2D;

	class TextComponent final : public IComponent
	{
	public:
		TextComponent(GameObject* owner, FVector2 position);
		virtual ~TextComponent();

		virtual void Update(float dt) override;
		virtual void Render() const override;

		void SetFont(const std::string& fontPath);
		void SetText(const std::string& text);
		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		void SetSize(int size);

	private:
		Font* m_pFont;
		std::string m_FontPath;
		int m_Size;
		Texture2D* m_pTexture;
		SDL_Color m_Color;
		std::string m_Text;
		
		FVector2 m_RelativeLocation;
		FVector2 m_WorldLocation;

		void CreateTexture();
	};
}


