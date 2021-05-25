#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputManager.h"

using GamepadButtonInfo = std::pair<const SHORT, fox::ActionCommand>;
using KeyboardButtonInfo = std::pair<const int, fox::ActionCommand>;

fox::InputComponent::InputComponent(GameObject* owner)
	: IComponent{ owner }
	, m_GamepadActionCommands{}
	, m_PlayerId{}
{
	m_PlayerId = InputManager::GetInstance().RegisterInputComponent(this);
}

void fox::InputComponent::ProcessInput()
{
		InputManager& inputManager = InputManager::GetInstance();
	
		for (GamepadButtonInfo& action : m_GamepadActionCommands)
		{
			bool pressed = inputManager.IsPressed(action.first);
			action.second.Execute(pressed);
		}

		for (KeyboardButtonInfo& action : m_KeyboardActionCommands)
		{
			bool pressed = inputManager.IsPressed(action.first);
			action.second.Execute(pressed);
		}
}

void fox::InputComponent::BindAction(SHORT gamepadButton, int keyboardKey, fox::ButtonState state, std::function<void(GameObject*)> fpAction)
{
	if (gamepadButton != -1)
	{
		m_GamepadActionCommands.insert(GamepadButtonInfo{ gamepadButton, fox::ActionCommand{ m_Owner, state, fpAction } });
	}
	
	if (keyboardKey != -1)
	{
		m_KeyboardActionCommands.insert(KeyboardButtonInfo{ keyboardKey , fox::ActionCommand{ m_Owner, state, fpAction } });
	}
}