#pragma once
#include "IComponent.h"

namespace fox
{
	class GameObject;
	class TextComponent;
}

class UI : public fox::IComponent
{
public:
	UI(fox::GameObject* owner, fox::TextComponent* scoreText, fox::TextComponent* healthText);
	~UI() = default;

	void UpdateScore(int score);
	void UpdateHealth(int health);

private:
	fox::TextComponent* m_ScoreText;
	fox::TextComponent* m_HealthText;
};