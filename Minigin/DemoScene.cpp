#include "MiniginPCH.h"
#include "DemoScene.h"

#include "TextureComponent.h"
#include "InputComponent.h"
#include "Transform.h"
#include "PlayFieldComponent.h"
#include "MoveComponent.h"

#include "Actions.h"

using namespace fox;

void DemoScene::LoadScene()
{
	//BACKGROUND
	GameObject* background{ new GameObject{this} };
	TextureComponent* backgroundTexture{ new TextureComponent{ background } };
	backgroundTexture->SetTexture("background.jpg");

	////LOGO
	//GameObject* DAE{ new GameObject {background} };
	//IComponent* DAETexture{ new TextureComponent{ DAE } };
	//static_cast<TextureComponent*>(DAETexture)->SetTexture("logo.png");

	////FOX
	//GameObject* fox{ new GameObject {this} };
	//fox->SetTransform({50.f, 50.f}, {0.f, 0.f}, {1.f, 1.f} );
	//IComponent* foxTexture{ new TextureComponent{fox} };
	//static_cast<TextureComponent*>(foxTexture)->SetTexture("fox.png");



	GameObject* PlayFieldObject{ new GameObject{this} };
	new PlayFieldComponent{ PlayFieldObject, "../Data/LevelLayout.txt" };

	GameObject* QBertObject{ new GameObject{this} };
	new TextureComponent{QBertObject, "fox.png"};
	new MoveComponent{ QBertObject };
	//InputComponent* QBertInput{ new InputComponent{QBertObject} };
}