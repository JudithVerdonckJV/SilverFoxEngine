#pragma once
#include <SDL.h>
#include "IComponent.h"

namespace fox
{
	class GameObject;
	class Font;
	class Texture2D;

    class FpsComponent final : public IComponent
    {
	public:
		FpsComponent(GameObject* owner);
		~FpsComponent();

		virtual void Render() const override;
		virtual void Update(float deltaTime) override;

		void SetFont(const std::string& fontPath);
		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		void SetSize(int size);

	private:
		Font* m_pFont;
		std::string m_FontPath;
		int m_Size;
		Texture2D* m_pTexture;
		SDL_Color m_Color;
		std::string m_Text;

		void CreateTexture();
    };
}


