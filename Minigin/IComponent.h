#pragma once

namespace fox
{
	class GameObject;

	class IComponent
	{
	public:
		IComponent(GameObject* owner);
		virtual ~IComponent() = default;
		
#pragma warning (push)
#pragma warning (disable: 4100)

		virtual void Update(float deltaTime) {};
		virtual void FixedUpdate(float tick) {};
		virtual void LateUpdate(float deltaTime) {};

		virtual void Render() const {};

		GameObject* GetOwner() const;

#pragma warning (pop)

		IComponent(const IComponent& other) = delete;
		IComponent(IComponent&& other) = delete;
		IComponent& operator=(const IComponent& other) = delete;
		IComponent& operator=(IComponent&& other) = delete;

	protected:
		GameObject* m_Owner;
	};
}


