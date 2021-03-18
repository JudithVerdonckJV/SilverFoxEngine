#pragma once
#include <vector>

#include "IComponent.h"

#include "Transform.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "InputComponent.h"
#include "FpsComponent.h"
#include "HealthComponent.h"

#include "Subject.h"

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


		Transform* GetTransform() const { return m_pTransform; };
		FVector2 GetLocation() const { return m_pTransform->Position(); };

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

	public:
		Subject* pSubject;

	private:
		std::vector<IComponent*> m_pComponents;
		Transform* m_pTransform;

	};
}
