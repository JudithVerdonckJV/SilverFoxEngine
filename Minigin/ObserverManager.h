#pragma once
#include <vector>
#include "Singleton.h"

namespace fox
{
	class Observer;

	class ObserverManager final : public Singleton<ObserverManager>
	{
	public:
		~ObserverManager();
		void AddObserver(Observer* observer);

	private:
		std::vector<Observer*> m_Observers{};
	};
}