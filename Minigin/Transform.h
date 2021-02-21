#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "IComponent.h"

namespace fox
{
	class Transform final : public IComponent
	{
	public:
		Transform();
		virtual ~Transform() = default;
		
		//position
		const FVector2& Position() const { return m_Position; }
		
		void SetPosition(float x, float y);
		void SetPosition(const FVector2& position);

		//rotation
		const FVector2& Rotation() const { return m_Rotation; };
		
		void SetRotation(float x, float y);
		void SetRotation(const FVector2& rotation);

		//scale
		const FVector2& Scale() const { return m_Scale; };
		
		void SetScale(float x, float y);
		void SetScale(const FVector2& scale);

	private:
		FVector2 m_Position;
		FVector2 m_Rotation;
		FVector2 m_Scale;
	};
}
