#include "MiniginPCH.h"
#include "InputComponent.h"
#include "InputManager.h"

using ButtonInfo = std::pair<const fox::ControllerButton, fox::ActionCommand>;
//using TriggerInfo = std::pair<const fox::ControllerTrigger, fox::TriggerCommand>;
//using StickInfo = std::pair<const fox::ControllerStick, fox::StickCommand>;

fox::InputComponent::InputComponent(GameObject* owner)
	: IComponent{ owner }
	, m_ActionCommands{}
	, m_PlayerId{}
{
	m_PlayerId = InputManager::GetInstance().RegisterInputComponent(this);
}

void fox::InputComponent::ProcessInput()
{
		InputManager& inputManager = InputManager::GetInstance();
	
		for (ButtonInfo& action : m_ActionCommands)
		{
			bool pressed = inputManager.IsPressed(action.first);
			action.second.Execute(pressed);
		}
}

void fox::InputComponent::BindAction(fox::ControllerButton button, fox::ButtonState state, std::function<void(GameObject*)> fpAction)
{
	m_ActionCommands.insert(ButtonInfo{ button, fox::ActionCommand{ m_Owner, state, fpAction } });
}



//void fox::InputComponent::BindTrigger(fox::ControllerTrigger trigger, std::function<void(float)> fpTrigger)
//{
//	m_TriggerCommands.insert(TriggerInfo{ trigger, fpTrigger });
//}
//
//void fox::InputComponent::BindThumb(fox::ControllerStick stick, std::function<void(FVector2)> fpStick)
//{
//	m_StickCommands.insert(StickInfo{ stick, fpStick });
//}

#pragma warning (push)
#pragma warning (disable: 4100)
//void fox::InputComponent::Update(float deltaTime)
//{
//	InputManager& inputManager = InputManager::GetInstance();
//	
//	for (ButtonInfo& action : m_ActionCommands)
//	{
//		bool pressed = inputManager.IsPressed(action.first);
//		action.second.Execute(m_Owner, pressed);
//	}
//
//	for (TriggerInfo& trigger : m_TriggerCommands)
//	{
//		float amount = inputManager.IsPressed(trigger.first);
//		trigger.second.Execute(amount);
//	}
//
//	for (StickInfo& stick : m_StickCommands)
//	{
//		FVector2 vector = inputManager.IsPressed(stick.first);
//		stick.second.Execute(vector);
//	}
//}
#pragma warning (pop)