#include "GamePch.h"
#include "ScoreMenu.h"

#include "GameObject.h"
#include "ButtonComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"

#include "SceneManager.h"
#include "QBertGameInstance.h"

void ScoreMenu::LoadScene()
{
	//BACKGROUND
	fox::GameObject* background{ new fox::GameObject{this} };
	fox::TextureComponent* backgroundTexture{ new fox::TextureComponent{ background } };
	backgroundTexture->SetTexture("background.jpg");

	//MAIN MENU BUTTON
	fox::GameObject* mainMenuButton{ new fox::GameObject{this} };
	mainMenuButton->SetLocation(230, 400);
	m_pMainMenuButton = new ButtonComponent{ mainMenuButton, 185, 45 };
	m_pMainMenuButton->SetNormalColor(SDL_Color{ 255, 255, 255, 255 });
	m_pMainMenuButton->SetHoveredColor(SDL_Color{ 200, 200, 200, 255 });
	fox::TextComponent* singleText = new fox::TextComponent{ mainMenuButton, {-30, -10} };
	singleText->SetText("MAIN MENU");
	singleText->SetColor(255, 0, 0, 255);

	//TEXT
	fox::GameObject* textObject{ new fox::GameObject{this} };
	fox::TextComponent* text{ new fox::TextComponent{textObject, {-170, -200}} };
	text->SetText("YOUR SCORE:");
	text->SetSize(50);

	//SCORE
	fox::GameObject* scoreObject{ new fox::GameObject{this} };
	m_pScore = new fox::TextComponent{scoreObject, {-250, -250}};
	m_pScore->SetText(std::to_string(QBertGameInstance::GetInstance().GetScore()));
	m_pScore->SetSize(50);
}

void ScoreMenu::Update(float)
{
	if (m_pMainMenuButton->IsClicked())
	{
		fox::SceneManager::GetInstance().SetActiveScene("MainMenu");
	}
}

void ScoreMenu::EnterScene()
{
	m_pScore->SetText(std::to_string(QBertGameInstance::GetInstance().GetScore()));
}