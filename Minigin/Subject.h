#pragma once
#include <vector>
#include "utils.h"

namespace fox
{
	class GameObject;
	class Observer;

	class Subject final
	{
	public:
		Subject() = default;
		~Subject() = default;

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* obsever);
		void Notify(GameObject* gameObject, Event eventName);

	private:
		std::vector<Observer*> m_Observers{};
	};
}