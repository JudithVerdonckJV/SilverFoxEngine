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




	class TriggerCommand
	{
	public:
		TriggerCommand(std::function<void(float)> fp);
		~TriggerCommand() = default;
		void Execute(float amount);

	private:
		std::function<void(float)> m_fpTrigger;
	};

	class StickCommand
	{
	public:
		StickCommand(std::function<void(FVector2)> fp);
		~StickCommand() = default;
		void Execute(FVector2 vector);

	private:
		std::function<void(FVector2)> m_fpStick;
	};
}

