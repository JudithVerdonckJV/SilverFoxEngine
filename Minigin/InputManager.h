#pragma once
#include <map>
#include <vector>
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")
#include "utils.h"
#include "Singleton.h"
#include "Commands.h"


namespace fox
{
	class InputComponent;

	class InputManager : public Singleton<InputManager>
	{
	public:
		~InputManager();
		
		bool ProcessInput();

		bool IsPressed(SHORT button) const;
		bool IsPressed(int button) const;
		

	private:
		XINPUT_STATE m_GamepadInputState;
		const UINT8* m_KeyboardInputState;
		std::vector<InputComponent*> m_pRegisteredInputComponents;
		
		friend class InputComponent;
		int RegisterInputComponent(InputComponent* inputComponent);

		friend class Singleton<InputManager>;
		InputManager();
	};
}