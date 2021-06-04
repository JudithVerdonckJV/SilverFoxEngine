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

	//PLAYERS
	m_pQBert1 = CreateQbert1Object(this, m_pPlayfield, m_pDiscs);
	m_pQBert2 = CreateQbert2Object(this, m_pPlayfield, m_pDiscs);
	m_PlayerCoily = CreatePlayerCoilyObject(this, m_pPlayfield, scoreObserver, m_pQBert1->GetOwner());

	//ENEMIES
	m_AICoily = CreateAICoilyObject(this, m_pPlayfield, scoreObserver, m_pQBert1->GetOwner());

	//ENEMYMANAGER
	GameObject* levelObject = new GameObject{ this };
	m_pLevelManager = new LevelManagerComponent{ levelObject, m_AICoily, m_PlayerCoily, nullptr, nullptr, nullptr, nullptr };

	//UI
	m_pUI = CreateUIObject(this);
}

void Level1::EnterScene()
{
	m_pLevelManager->DespawnAll();
	m_pPlayfield->Reset();
	m_pDiscs->Reset();
	m_pGameInstance->SetUI(m_pUI);

	EGameModes mode = m_pGameInstance->GameMode;

	switch (mode)
	{
	case EGameModes::Single:
		m_pQBert2->GetOwner()->SetActive(false);
		m_pQBert2->GetOwner()->SetVisibility(false);
		m_pQBert1->SetSpawnIndex(0);
		m_pLevelManager->CoilyIsPlayer(false);
		break;
	case EGameModes::Versus:
		m_pQBert2->GetOwner()->SetActive(false);
		m_pQBert2->GetOwner()->SetVisibility(false);
		m_pLevelManager->CoilyIsPlayer(true);
		break;
	case EGameModes::Coop:
		m_PlayerCoily->GetOwner()->SetActive(false);
		m_PlayerCoily->GetOwner()->SetVisibility(false);
		m_pQBert1->SetSpawnIndex(21);
		m_pQBert2->SetSpawnIndex(27);		
		break;
	}

	m_pQBert1->Reset();
	m_pQBert2->Reset();
}

void Level1::Update(float)
{
	if (m_pQBert1->HasDied)
	{
		m_pQBert1->HasDied = false;
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