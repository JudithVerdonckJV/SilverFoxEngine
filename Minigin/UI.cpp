#include "MiniginPCH.h"
#include "UI.h"

#include "GameObject.h"
#include "TextComponent.h"

UI::UI(fox::GameObject* owner, fox::TextComponent* scoreText, fox::TextComponent* healthText)
	:IComponent{ owner }
	, m_ScoreText{ scoreText }
	, m_HealthText{ healthText }
{
}

void UI::UpdateScore(int score)
{
	m_ScoreText->SetText(std::to_string(score));
}

void UI::UpdateHealth(int health)
{
	m_HealthText->SetText(std::to_string(health));
}