#include "MiniginPCH.h"
#include "LevelChange1.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"

#include "SceneManager.h"

void LevelChange1::LoadScene()
{
	//BACKGROUND
	fox::GameObject* background{ new fox::GameObject{this} };
	fox::TextureComponent* backgroundTexture{ new fox::TextureComponent{ background } };
	backgroundTexture->SetTexture("background.jpg");
	
	//TEXT
	fox::GameObject* textObject{ new fox::GameObject{this} };
	fox::TextComponent* text{ new fox::TextComponent{textObject, {-250, -200}} };
	text->SetText("Level 2");
	text->SetSize(50);

	m_CurrentTimer = 0.f;
	m_MaxTimer = 2.f;
}

void LevelChange1::Update(float dt)
{
	m_CurrentTimer += dt;
	if (m_CurrentTimer >= m_MaxTimer)
	{
		m_CurrentTimer = 0.f;
		fox::SceneManager::GetInstance().SetActiveScene("Level2");
	}
}