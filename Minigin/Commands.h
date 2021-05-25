#pragma once
#include <functional>
#include "utils.h"

namespace fox
{
	class GameObject;
	
	enum class ButtonState
	{
		ButtonDown,
		ButtonUp,
	};

	class ActionCommand
	{
	public:
		ActionCommand(GameObject* owner, ButtonState state, std::function<void(GameObject*)> fp);
		~ActionCommand() = default;
		void Execute(bool pressed);

	private:
		GameObject* m_Owner;
		ButtonState m_ButtonState;
		std::function<void(GameObject*)> m_fpAction;
		bool m_LastState;
	};
}

