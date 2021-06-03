#include "MiniginPCH.h"
#include "Level1.h"

#include "GameStatics.h"
#include "SceneManager.h"

#include "Transform.h"
#include "LevelManagerComponent.h"

#include "Actions.h"
#include "Enums.h"

#include "SceneSetupHelpers.h"
#include "QBertGameInstance.h"

using namespace fox;

void Level1::LoadScene()
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
	m_pDiscs = new DiscsComponent{ discsObject, "../Data/LevelLayout.txt", m_pPlayfield };
	SubjectComponent* discSubject{ new SubjectComponent{discsObject} };
	discSubject->AddObserver(scoreObserver);

	//PLAYER(S)
	m_pQBert = CreateQbertObject(this, m_pPlayfield, m_pDiscs);

	//ENEMIES
	Coily_Behavior* coilyBehavior = CreateCoilyObject(this, m_pPlayfield, scoreObserver, m_pQBert->GetOwner());

	//ENEMYMANAGER
	GameObject* levelObject = new GameObject{ this };
	m_pLevelManager = new LevelManagerComponent{ levelObject, coilyBehavior, nullptr, nullptr, nullptr, nullptr };

	//UI
	m_pUI = CreateUIObject(this);
}

void Level1::EnterScene()
{
	m_pLevelManager->DespawnAll();
	m_pPlayfield->Reset();
	m_pDiscs->Reset();
	m_pQBert->Reset();
	m_pGameInstance->SetUI(m_pUI);
}

void Level1::Update(float)
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
		SceneManager::GetInstance().SetActiveScene("LevelChange1");
	}
}