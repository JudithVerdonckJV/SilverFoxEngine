#include "MiniginPCH.h"
#include <string>
#include <functional>
#include "PlayerState.h"

using EventInfo = std::pair<const std::string, std::function<void(fox::GameObject*)>>;

fox::PlayerState::PlayerState()
{
}

fox::PlayerState::~PlayerState()
{
}

void fox::PlayerState::OnNotify(fox::GameObject* , const std::string&)
{
	//switch (event)
	//{
	//case Event::HealthChange:
	//	OnHealthChange(pSubject);
	//}
}

void fox::PlayerState::OnHealthChange(fox::GameObject* )
{
	//float health = pSubject->GetComponent<HealthComponent>()->GetCurrentHealth();
	//TextComponent* text = pSubject->GetComponent<TextComponent>();
	//if (text != nullptr) text->SetText("Health is " + std::to_string((int)health));
}

//#pragma warning (push)
//#pragma warning (disable: 4100)
//void OnPlayerDeath(fox::GameObject* gameObject)
//{
//	std::cout << "MESSAGES RECEIVED: PLAYERDEATH\n";
//}
//#pragma warning (pop)
//
////void OnScoreIncrease(fox::GameObject* gameObject)
////{
////
////}