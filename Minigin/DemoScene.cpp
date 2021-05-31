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
	PlayFieldComponent* playfieldComponent{ new PlayFieldComponent{ playFieldObject, "../Data/LevelLayout.txt", ETileBehavior::OneFlip } };

	//DISCS
	GameObject* discsObject{ new GameObject{this} };
	DiscsComponent* discComponent{ new DiscsComponent{discsObject, "../Data/LevelLayout.txt", playfieldComponent} };

	//PLAYER - QBERT
	QBert_Behavior* qbertBehavior = CreateQbertObject(this, playfieldComponent, discComponent);

	//UGG
	Ugg_Behavior* uggBehavior = CreateUggObject(this, playfieldComponent);

	//WRONGWAY
	Wrongway_Behavior* wrongwayBehavior = CreateWrongwayObject(this, playfieldComponent);

	//SAM
	SlickAndSam_Behavior* slickBehavior = CreateSlickObject(this, playfieldComponent);

	//SLICK
	SlickAndSam_Behavior* samBehavior = CreateSlickObject(this, playfieldComponent);

	//COILY
	Coily_Behavior* coilyBehavior = CreateCoilyObject(this, playfieldComponent);

	//LEVELMANAGER
	GameObject* levelObject = new GameObject{ this };
	new LevelManagerComponent{ levelObject, playfieldComponent, qbertBehavior, coilyBehavior, slickBehavior, samBehavior, uggBehavior, wrongwayBehavior };
}