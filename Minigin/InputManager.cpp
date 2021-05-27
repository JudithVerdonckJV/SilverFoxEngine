#include "MiniginPCH.h"
#include <SDL.h>
#include "GameStatics.h"
#include "InputManager.h"
#include "InputComponent.h"

fox::InputManager::InputManager()
	: m_pRegisteredInputComponents{}
	, m_GamepadInputState{}
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
