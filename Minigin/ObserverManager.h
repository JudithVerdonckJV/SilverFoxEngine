#pragma once
#include <vector>
#include "Singleton.h"

namespace fox
{
	class IObserver;

	class ObserverManager final : public Singleton<ObserverManager>
	{
	public:
		~ObserverManager();
		void AddObserver(IObserver* observer);

	private:
		std::vector<IObserver*> m_Observers{};
	};
}