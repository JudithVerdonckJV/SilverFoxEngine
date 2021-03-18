#include "MiniginPCH.h"
#include "Commands.h"
#include "GameObject.h"

fox::ActionCommand::ActionCommand(GameObject* owner, fox::ButtonState state, std::function<void(fox::GameObject*)> fp)
	: m_Owner{ owner }
	, m_fpAction{ fp }
	, m_ButtonState{ state }
	, m_LastState{ false }
{
}

void fox::ActionCommand::Execute(bool pressed)
{
	if (m_ButtonState == fox::ButtonState::ButtonDown)
	{
		if (pressed && !m_LastState) m_fpAction(m_Owner);
	}

	else if (m_ButtonState == fox::ButtonState::ButtonUp)
	{
		if (!pressed && m_LastState) m_fpAction(m_Owner);
	}

	m_LastState = pressed;
}



fox::TriggerCommand::TriggerCommand(std::function<void(float)> fp)
	: m_fpTrigger{ fp }
{
}

void fox::TriggerCommand::Execute(float amount)
{
	m_fpTrigger(amount);
}

fox::StickCommand::StickCommand(std::function<void(FVector2)> fp)
	: m_fpStick{ fp }
{
}

void fox::StickCommand::Execute(FVector2 vector)
{
	m_fpStick(vector);
}