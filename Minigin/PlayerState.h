#pragma once
#include "Observer.h"
#include "GameObject.h"

namespace fox
{
	class PlayerState final : public Observer
	{
	public:
		PlayerState();
		~PlayerState();

		virtual void OnNotify(GameObject* pSubject, Event event) override;

	private:
		void OnHealthChange(fox::GameObject* gameObject);
		//void OnScoreIncrease(fox::GameObject* gameObject);
	};
}