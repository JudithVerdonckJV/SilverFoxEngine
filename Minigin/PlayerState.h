#pragma once
#include "IObserver.h"
#include "GameObject.h"

namespace fox
{
	class PlayerState final : public IObserver
	{
	public:
		PlayerState();
		~PlayerState();

		virtual void OnNotify(GameObject* pSubject, const std::string& event) override;

	private:

		void OnHealthChange(fox::GameObject* gameObject);
		//void OnScoreIncrease(fox::GameObject* gameObject);
	};
}