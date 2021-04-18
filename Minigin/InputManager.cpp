#include "MiniginPCH.h"
#include "InputManager.h"
#include "InputComponent.h"

fox::InputManager::InputManager()
	: m_pRegisteredInputComponents{}
	, m_InputState{}
{
}

fox::InputManager::~InputManager()
{
}

int fox::InputManager::RegisterInputComponent(InputComponent* inputComponent)
{
	m_pRegisteredInputComponents.push_back(inputComponent);
	return int(m_pRegisteredInputComponents.size());
}

bool fox::InputManager::ProcessInput()
{
	

	for (size_t player{}; player < m_pRegisteredInputComponents.size(); ++player)
	{
		
		ZeroMemory(&m_InputState, sizeof(XINPUT_STATE));
		XInputGetState((DWORD)player, &m_InputState);
		m_pRegisteredInputComponents[player]->ProcessInput();
	}
	return true; // TODO: EXIT
}

bool fox::InputManager::IsPressed(ControllerButton button) const
{
	return m_InputState.Gamepad.wButtons & WORD(button);
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