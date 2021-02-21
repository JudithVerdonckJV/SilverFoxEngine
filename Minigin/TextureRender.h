#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "Texture2D.h"
#include "IComponent.h"

namespace fox
{
	class TextureRender final : public IComponent
	{
	public:
		TextureRender() = default;
		TextureRender(const std::string& textPath);
		virtual ~TextureRender();

		virtual void Render(const FVector2& position) const override;

		void SetTexture(const std::string& textPath);
		void SetLocalPos(const FVector2& localPos);
		void SetLocalPos(float x, float y);

	private:
		Texture2D* m_pTexture;
		FVector2 m_LocalPos;
	};
}
