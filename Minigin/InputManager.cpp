#include "MiniginPCH.h"
#include <SDL.h>
#include "GameStatics.h"
#include "InputManager.h"
#include "InputComponent.h"

fox::InputManager::InputManager()
	: m_pRegisteredInputComponents{}
	, m_GamepadInputState{}
	, m_KeyboardInputState{}
{
}

fox::InputManager::~InputManager()
{
}

int fox::InputManager::RegisterInputComponent(InputComponent* inputComponent)
{
	m_pRegisteredInputComponents.push_back(inputComponent);
	GameStatics::m_Players.push_back(inputComponent->GetOwner());
	return int(m_pRegisteredInputComponents.size());
}

bool fox::InputManager::ProcessInput()
{
	SDL_Event e{};
	while (SDL_PollEvent(&e) > 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
			break;
		default:
			break;
		}
	}

	//gamepad
	for (size_t player{}; player < m_pRegisteredInputComponents.size(); ++player)
	{
		ZeroMemory(&m_GamepadInputState, sizeof(XINPUT_STATE));
		XInputGetState((DWORD)player, &m_GamepadInputState);
		m_pRegisteredInputComponents[player]->ProcessInput();
	}

	//keyboard
	m_KeyboardInputState = SDL_GetKeyboardState( nullptr );

	return true;
}

bool fox::InputManager::IsPressed(SHORT button) const
{
	return m_GamepadInputState.Gamepad.wButtons & button;
}

bool fox::InputManager::IsPressed(int button) const
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	return pStates[button];
}

//float fox::InputManager::IsPressed(ControllerTrigger axis) const
//{
//	switch (axis)
//	{
//	case ControllerTrigger::LeftTrigger:
//		return m_InputState.Gamepad.bLeftTrigger;
//		break;
//	case ControllerTrigger::RightTrigger:
//		return m_InputState.Gamepad.bRightTrigger;
//		break;
//	}
//	return 0.f;
//}
//
//FVector2 fox::InputManager::IsPressed(ControllerStick stick) const
//{
//	switch (stick)
//	{
//	case ControllerStick::LeftThumb:
//		return FVector2{ (float)m_InputState.Gamepad.sThumbLX, (float)m_InputState.Gamepad.sThumbLY };
//		break;
//	case ControllerStick::RightThumb:
//		return FVector2{ (float)m_InputState.Gamepad.sThumbRX, (float)m_InputState.Gamepad.sThumbRY };
//		break;
//	}
//	return { 0.f, 0.f };
//}