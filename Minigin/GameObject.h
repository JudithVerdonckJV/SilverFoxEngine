#pragma once
#include <vector>
#include <string>

#include "IComponent.h"
#include "utils.h"

namespace fox
{
	class Transform;
	class SubjectComponent;
	class InputComponent;
	class Scene;

	class GameObject final
	{
	public:
		GameObject(GameObject* owner);
		GameObject(Scene* owner);
		~GameObject();

		void Update(float deltaTime);
		void FixedUpdate(float tick);
		void LateUpdate(float deltaTime);

		void Render() const;

		void SetTransform(const FVector2& position, const FVector2& rotation, const FVector2& scale);
		Transform* GetTransform() const;
		void SetLocation(float x, float y);
		void SetLocation(const FVector2& xy);
		FVector2 GetLocation() const;

		const SubjectComponent* GetSubject() const;
		IComponent* GetUserComponent() const;

		void SetUserComponent(IComponent* component);

		void SetTag(const std::string& tag);
		const std::string& GetTag() const;

		GameObject* GetChildByTag(const std::string& tag) const;
		GameObject* GetChildByIndex(size_t index) const;

		template <typename T>
		T* GetComponent()
		{
			for (IComponent* bc : m_pComponents)
			{
				if (dynamic_cast<T*>(bc))
					return (T*)bc;
			}
			return nullptr;
		}

	private:
		friend class IComponent;
		void AddComponent(IComponent* const component);

		void AddChild(GameObject* const childObject);

		GameObject* m_Owner;
		std::vector<IComponent*> m_pComponents;
		std::vector<GameObject*> m_pChildObjects;
		
		//fast access
		Transform* m_pTransform;
		SubjectComponent* m_pSubject;

		IComponent* m_UserComponent;

		std::string m_Tag;
	};
}
