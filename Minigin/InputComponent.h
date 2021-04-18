#pragma once
#include "IComponent.h"
#include <map>
#include "InputManager.h"
#include "Commands.h"

namespace fox
{
	class GameObject;

	class InputComponent final : public IComponent
	{
	public:
		InputComponent(GameObject* owner);
		~InputComponent() = default;

		void ProcessInput();

		void BindAction(ControllerButton button, ButtonState state, std::function<void(GameObject*)> fpAction);
		//void BindTrigger(ControllerTrigger axis, std::function<void(float)> fpTrigger);
		//void BindThumb(ControllerStick stick, std::function<void(FVector2)> fpStick);

	private:
		std::map<fox::ControllerButton, ActionCommand> m_ActionCommands;
		//std::map<fox::ControllerTrigger, TriggerCommand> m_TriggerCommands;
		//std::map<fox::ControllerStick, StickCommand> m_StickCommands;

		int m_PlayerId;
	};
}