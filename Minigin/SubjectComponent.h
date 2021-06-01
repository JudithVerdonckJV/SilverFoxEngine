#pragma once
#include "IComponent.h"

namespace fox
{
	class GameObject;
	class IObserver;

	class SubjectComponent final : public IComponent
	{
	public:
		SubjectComponent(GameObject* owner);
		virtual ~SubjectComponent() = default;

		void AddObserver(IObserver* observer);
		void RemoveObserver(IObserver* obsever);
		void Notify(GameObject* gameObject, int eventName);

	private:
		std::vector<IObserver*> m_pObservers{};
	};
}