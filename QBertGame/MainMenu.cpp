#include "GamePch.h"
#include "MainMenu.h"
#include "ServiceLocator.h"

#include "GameObject.h"
#include "ButtonComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"

#include "SceneManager.h"
#include "QBertGameInstance.h"

#include "Enums.h"

void MainMenu::LoadScene()
{
	//BACKGROUND
	fox::GameObject* background{ new fox::GameObject{this} };
	fox::TextureComponent* backgroundTexture{ new fox::TextureComponent{ background } };
	backgroundTexture->SetTexture("background.jpg");
	
	//SINGLE PLAYER
	fox::GameObject* singleplayerButton{ new fox::GameObject{this} };
	singleplayerButton->SetLocation(230, 150);
	m_pSinglePlayerButton = new ButtonComponent{ singleplayerButton, 185, 45 };
	m_pSinglePlayerButton->SetNormalColor(SDL_Color{ 255, 255, 255, 255 });
	m_pSinglePlayerButton->SetHoveredColor(SDL_Color{ 200, 200, 200, 255 });
	fox::TextComponent* singleText = new fox::TextComponent{ singleplayerButton, {-10, -10} };
	singleText->SetText("SINGLEPLAYER");
	singleText->SetColor(255, 0, 0, 255);

	//VERSUS
	fox::GameObject* versusButton{ new fox::GameObject{this} };
	versusButton->SetLocation(230, 200);
	m_pVersusButton = new ButtonComponent{ versusButton, 185, 45 };
	m_pVersusButton->SetNormalColor(SDL_Color{ 255, 255, 255, 255 });
	m_pVersusButton->SetHoveredColor(SDL_Color{ 200, 200, 200, 255 });
	fox::TextComponent* versusText = new fox::TextComponent{ versusButton, {-50, -10} };
	versusText->SetText("VERSUS");
	versusText->SetColor(255, 0, 0, 255);

	//COOP
	fox::GameObject* coopButton{ new fox::GameObject{this} };
	coopButton->SetLocation(230, 250);
	m_pCoopButton = new ButtonComponent{ coopButton, 185, 45 };
	m_pCoopButton->SetNormalColor(SDL_Color{ 255, 255, 255, 255 });
	m_pCoopButton->SetHoveredColor(SDL_Color{ 200, 200, 200, 255 });
	fox::TextComponent* coopText = new fox::TextComponent{ coopButton, {-65, -10} };
	coopText->SetText("COOP");
	coopText->SetColor(255, 0, 0, 255);


	//LOADING IN SOUND
	ServiceLocator::GetSoundSystem();
	//ss.AddSound((int)ESounds::QBertJump, "Sound/jump-3.mp3");
}

void MainMenu::Update(float )
{
	if (m_pSinglePlayerButton->IsClicked())
	{
		fox::SceneManager::GetInstance().SetActiveScene("LevelChange0");
		QBertGameInstance::GetInstance().GameMode = EGameModes::Single;
	}

	if (m_pVersusButton->IsClicked())
	{
		fox::SceneManager::GetInstance().SetActiveScene("LevelChange0");
		QBertGameInstance::GetInstance().GameMode = EGameModes::Versus;
	}

	if (m_pCoopButton->IsClicked())
	{
		fox::SceneManager::GetInstance().SetActiveScene("LevelChange0");
		QBertGameInstance::GetInstance().GameMode = EGameModes::Coop;
	}
}

void MainMenu::EnterScene()
{
	QBertGameInstance::GetInstance().Reset();
}