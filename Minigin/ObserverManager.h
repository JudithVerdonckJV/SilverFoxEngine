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

	private:
		friend class IObserver;
		void AddObserver(IObserver* observer);

		std::vector<IObserver*> m_Observers{};
	};
}