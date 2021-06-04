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
		virtual ~InputComponent() = default;

		void ProcessInput();

		void BindAction(int controllerButton, int keyboardKey, ButtonState state, std::function<void(GameObject*)> fpAction);

	private:
		std::map<int, ActionCommand> m_GamepadActionCommands;
		std::map<int, ActionCommand> m_KeyboardActionCommands;

		int m_PlayerId;
	};
}