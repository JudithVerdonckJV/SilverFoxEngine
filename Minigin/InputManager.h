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
	enum class ControllerButton : WORD
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ArrowUp = XINPUT_GAMEPAD_DPAD_UP,
		ArrowDown = XINPUT_GAMEPAD_DPAD_DOWN,
		ArrowLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ArrowRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	};

	//enum class ControllerTrigger
	//{
	//	LeftTrigger,
	//	RightTrigger
	//};

	//enum class ControllerStick
	//{
	//	LeftThumb,
	//	RightThumb,
	//};



	class InputComponent;

	class InputManager : public Singleton<InputManager>
	{
	public:
		~InputManager();
		
		bool ProcessInput();

		bool IsPressed(ControllerButton button) const;
		//float IsPressed(ControllerTrigger trigger) const;
		//FVector2 IsPressed(ControllerStick stick) const;

	private:
		XINPUT_STATE m_InputState;
		std::vector<InputComponent*> m_pRegisteredInputComponents;
		
		friend class InputComponent;
		int RegisterInputComponent(InputComponent* inputComponent);

		

		friend class Singleton<InputManager>;
		InputManager();
	};
}