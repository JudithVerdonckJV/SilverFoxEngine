#pragma once
#include "utils.h"

namespace fox
{
	class IComponent
	{
	public:
		enum class ComponentID
		{
			Transform = 0,
			Texture = 1,
			Font = 2,
			FPS = 3
		};

	public:
		IComponent() = default;
		virtual ~IComponent() = default;

		ComponentID Id() const;
		
#pragma warning (push)
#pragma warning (disable: 4100)
		virtual void Update(float deltaTime) {};
		virtual void FixedUpdate(float tick) {};
		virtual void LateUpdate(float deltaTime) {};

		virtual void Render(const FVector2& position) const {};
#pragma warning (pop)

		IComponent(const IComponent& other) = delete;
		IComponent(IComponent&& other) = delete;
		IComponent& operator=(const IComponent& other) = delete;
		IComponent& operator=(IComponent&& other) = delete;

	protected:
		ComponentID m_Id{};
	};
}


