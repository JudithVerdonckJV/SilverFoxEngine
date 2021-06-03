#include "MiniginPCH.h"
#include "Level2.h"

#include "SceneManager.h"

#include "Transform.h"
#include "LevelManagerComponent.h"

#include "Actions.h"
#include "Enums.h"

#include "SceneSetupHelpers.h"
#include "QBertGameInstance.h"

using namespace fox;

void Level2::LoadScene()
{
	m_pGameInstance = &QBertGameInstance::GetInstance();
	ScoreObserver* scoreObserver{ new ScoreObserver{} };

	//BACKGROUND
	GameObject* background{ new GameObject{this} };
	TextureComponent* backgroundTexture{ new TextureComponent{ background } };
	backgroundTexture->SetTexture("background.jpg");

	//LEVEL
	GameObject* playFieldObject{ new GameObject{this} };
	m_pPlayfield = new PlayFieldComponent{ playFieldObject, "../Data/LevelLayout.txt", ETileBehavior::TwoFlips };
	SubjectComponent* playfieldSubject{ new SubjectComponent{playFieldObject} };
	playfieldSubject->AddObserver(scoreObserver);

	//DISCS
	GameObject* discsObject{ new GameObject{this} };
	m_pDiscs = new DiscsComponent{ discsObject, "../Data/LevelLayout.txt", m_pPlayfield };
	SubjectComponent* discSubject{ new SubjectComponent{discsObject} };
	discSubject->AddObserver(scoreObserver);


	//PLAYER(S)
	m_pQBert = CreateQbertObject(this, m_pPlayfield, m_pDiscs);

	//ENEMIES
	SlickAndSam_Behavior* slickBehavior = CreateSlickObject(this, m_pPlayfield, scoreObserver);
	SlickAndSam_Behavior* samBehavior = CreateSamObject(this, m_pPlayfield, scoreObserver);
	Coily_Behavior* coilyBehavior = CreateCoilyObject(this, m_pPlayfield, scoreObserver, m_pQBert->GetOwner());

	//ENEMYMANAGER
	GameObject* levelObject = new GameObject{ this };
	m_pLevelManager = new LevelManagerComponent{ levelObject, coilyBehavior, slickBehavior, samBehavior, nullptr, nullptr };

	//UI
	m_pUI = CreateUIObject(this);

}

void Level2::EnterScene()
{
	m_pLevelManager->DespawnAll();
	m_pQBert->Reset();
	m_pPlayfield->Reset();
	m_pDiscs->Reset();
	m_pGameInstance->SetUI(m_pUI);
}

void Level2::Update(float)
{
	if (m_pQBert->HasDied)
	{
		m_pQBert->HasDied = false;
		m_pLevelManager->DespawnAll();

		m_pGameInstance->ChangeHealth(-1);
		if (m_pGameInstance->GetHealth() < 0)
		{
			SceneManager::GetInstance().SetActiveScene("ScoreMenu");
		}
	}

	if (m_pPlayfield->LevelFinished())
	{
		m_pDiscs->ScoreRemainingDiscNr();
		SceneManager::GetInstance().SetActiveScene("LevelChange2");
	}
}