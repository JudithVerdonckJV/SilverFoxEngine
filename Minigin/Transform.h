#pragma once
#include "IComponent.h"
#include "utils.h"

namespace fox
{
	class Transform final : public IComponent
	{
	public:
		Transform(GameObject* owner);
		Transform(const FVector2& location, const FVector2& rotation, const FVector2& scale);
		virtual ~Transform() = default;
		
		//position
		const FVector2& Location() const { return m_Location; }
		
		void SetLocation(float x, float y);
		void SetLocation(const FVector2& position);

		//rotation
		const FVector2& Rotation() const { return m_Rotation; };
		
		void SetRotation(float x, float y);
		void SetRotation(const FVector2& rotation);

		//scale
		const FVector2& Scale() const { return m_Scale; };
		
		void SetScale(float x, float y);
		void SetScale(const FVector2& scale);

	private:
		FVector2 m_Location;
		FVector2 m_Rotation;
		FVector2 m_Scale;
	};
}
