#include "MiniginPCH.h"
#include "DemoScene.h"

#include "Transform.h"
#include "PlayFieldComponent.h"
#include "DiscsComponent.h"
#include "LevelManagerComponent.h"

#include "QBert_Behavior.h"
#include "Ugg_Behavior.h"
#include "Wrongway_Behavior.h"
#include "SlickAndSam_Behavior.h"
#include "Coily_Behavior.h"

#include "Actions.h"
#include "Enums.h"
#include "SceneSetupHelpers.h"

using namespace fox;

void DemoScene::LoadScene()
{
	//BACKGROUND
	GameObject* background{ new GameObject{this} };
	TextureComponent* backgroundTexture{ new TextureComponent{ background } };
	backgroundTexture->SetTexture("background.jpg");

	//LEVEL
	GameObject* playFieldObject{ new GameObject{this} };
	m_pPlayfield = new PlayFieldComponent{ playFieldObject, "../Data/LevelLayout.txt", ETileBehavior::OneFlip };

	//DISCS
	GameObject* discsObject{ new GameObject{this} };
	m_pDiscs = new DiscsComponent{discsObject, "../Data/LevelLayout.txt", m_pPlayfield};

	//PLAYER(S)
	m_pQBert = CreateQbertObject(this, m_pPlayfield, m_pDiscs);

	//ENEMIES
	Ugg_Behavior* uggBehavior = CreateUggObject(this, m_pPlayfield);
	Wrongway_Behavior* wrongwayBehavior = CreateWrongwayObject(this, m_pPlayfield);
	SlickAndSam_Behavior* slickBehavior = CreateSlickObject(this, m_pPlayfield);
	SlickAndSam_Behavior* samBehavior = CreateSlickObject(this, m_pPlayfield);
	Coily_Behavior* coilyBehavior = CreateCoilyObject(this, m_pPlayfield);

	//ENEMYMANAGER
	GameObject* levelObject = new GameObject{ this };
	m_pLevelManager = new LevelManagerComponent{ levelObject, coilyBehavior, slickBehavior, samBehavior, uggBehavior, wrongwayBehavior };
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
	}

	if (m_pPlayfield->LevelFinished())
	{
		//open next level
	}
}