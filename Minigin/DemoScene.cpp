#include "MiniginPCH.h"
#include "DemoScene.h"

#include "SceneManager.h"

#include "Transform.h"
#include "LevelManagerComponent.h"

#include "Actions.h"
#include "Enums.h"

#include "SceneSetupHelpers.h"
#include "QBertGameInstance.h"

using namespace fox;

void DemoScene::LoadScene()
{		
	m_pGameInstance = &QBertGameInstance::GetInstance();
	ScoreObserver* scoreObserver{ new ScoreObserver{} };
	
	//BACKGROUND
	GameObject* background{ new GameObject{this} };
	TextureComponent* backgroundTexture{ new TextureComponent{ background } };
	backgroundTexture->SetTexture("background.jpg");

	//LEVEL
	GameObject* playFieldObject{ new GameObject{this} };
	m_pPlayfield = new PlayFieldComponent{ playFieldObject, "../Data/LevelLayout.txt", ETileBehavior::OneFlip };
	SubjectComponent* playfieldSubject{ new SubjectComponent{playFieldObject} };
	playfieldSubject->AddObserver(scoreObserver);

	//DISCS
	GameObject* discsObject{ new GameObject{this} };
	m_pDiscs = new DiscsComponent{discsObject, "../Data/LevelLayout.txt", m_pPlayfield};
	SubjectComponent* discSubject{ new SubjectComponent{discsObject} };
	discSubject->AddObserver(scoreObserver);


	//PLAYER(S)
	m_pQBert = CreateQbertObject(this, m_pPlayfield, m_pDiscs);

	//ENEMIES
	Ugg_Behavior* uggBehavior = CreateUggObject(this, m_pPlayfield);
	Wrongway_Behavior* wrongwayBehavior = CreateWrongwayObject(this, m_pPlayfield);
	SlickAndSam_Behavior* slickBehavior = CreateSlickObject(this, m_pPlayfield, scoreObserver);
	SlickAndSam_Behavior* samBehavior = CreateSamObject(this, m_pPlayfield, scoreObserver);
	Coily_Behavior* coilyBehavior = CreateCoilyObject(this, m_pPlayfield, scoreObserver, m_pQBert->GetOwner());

	//ENEMYMANAGER
	GameObject* levelObject = new GameObject{ this };
	m_pLevelManager = new LevelManagerComponent{ levelObject, coilyBehavior, slickBehavior, samBehavior, uggBehavior, wrongwayBehavior };

	//UI
	GameObject* uiObject{ new GameObject{this} };
	TextComponent* scoreText{ new TextComponent{uiObject, {0.f, -5.f}} };
	scoreText->SetText("Score: ");
	TextComponent* healthText{ new TextComponent{uiObject, {0.f, -30.f}} };
	healthText->SetText("Health: ");
	TextComponent* scoreNr{ new TextComponent{uiObject, {-90.f, -5.f}} };
	TextComponent* healthNr{ new TextComponent{uiObject, {-90.f, -30.f}} };
	UI* ui{ new UI{uiObject, scoreNr, healthNr} };

	m_pGameInstance->SetUI(ui);
}

void DemoScene::EnterScene()
{
	m_pLevelManager->DespawnAll();
	m_pPlayfield->Reset();
	m_pDiscs->Reset();
}

void DemoScene::Update(float )
{
	if (m_pQBert->HasDied)
	{
		m_pQBert->HasDied = false;
		m_pLevelManager->DespawnAll();

		m_pGameInstance->ChangeHealth(-1);
		if (m_pGameInstance->GetHealth() < 0)
		{
			//open main menu
		}
	}

	if (m_pPlayfield->LevelFinished())
	{
		m_pDiscs->ScoreRemainingDiscNr();
		SceneManager::GetInstance().SetActiveScene("Level1");
	}
}