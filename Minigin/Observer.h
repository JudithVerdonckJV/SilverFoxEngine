#pragma once
#include <map>
#include <functional>
#include "utils.h"

namespace fox
{
	class GameObject;

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		virtual void OnNotify(GameObject* pSubject, Event event) = 0;
	};
}