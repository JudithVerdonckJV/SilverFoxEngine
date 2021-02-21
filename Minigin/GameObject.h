#pragma once
#include <vector>

#include "IComponent.h"

#include "Transform.h"
#include "TextureRender.h"
#include "FontRender.h"
#include "FPS.h"

namespace fox
{
	class GameObject final
	{
	public:
		GameObject();
		~GameObject();
		
		void Update(float deltaTime);
		void FixedUpdate(float tick);
		void LateUpdate(float deltaTime);
		
		void Render() const;
		
		void AddComponent(IComponent* const component);

		template <typename T>
		T* GetComponent(IComponent::ComponentID id)
		{
			if (id == m_pTransform->Id())
			{
				return m_pTransform;
			}

			for (IComponent* comp : m_pComponents)
			{
				if (id == comp->Id())
				{
					return static_cast<T*>(comp);
				}
			}

			throw "Component not found on gameobject!";
		}

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<IComponent*> m_pComponents;
		Transform* m_pTransform;
	};
}
