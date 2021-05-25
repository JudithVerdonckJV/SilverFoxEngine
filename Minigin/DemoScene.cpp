#include "MiniginPCH.h"
#include "DemoScene.h"

#include "TextureComponent.h"
#include "InputComponent.h"
#include "Transform.h"
#include "PlayFieldComponent.h"
#include "GridMovementComponent.h"

#include "Actions.h"

using namespace fox;

void DemoScene::LoadScene()
{
	//BACKGROUND
	GameObject* background{ new GameObject{this} };
	TextureComponent* backgroundTexture{ new TextureComponent{ background } };
	backgroundTexture->SetTexture("background.jpg");

	//LEVEL
	GameObject* playFieldObject{ new GameObject{this} };
	PlayFieldComponent* playfieldComponent{ new PlayFieldComponent{ playFieldObject, "../Data/LevelLayout.txt" } };

	//PLAYER
	GameObject* QBertObject{ new GameObject{this} };
	new TextureComponent{QBertObject, "fox.png"};
	GridMovementComponent* gridMovement{ new GridMovementComponent{ QBertObject, playfieldComponent } };
	InputComponent* QBertInput{ new InputComponent{QBertObject} };
	QBertObject->SetUserComponent(gridMovement);

	QBertInput->BindAction(ControllerButton::ArrowDown, ButtonState::ButtonDown, &MoveDownLeft);
	QBertInput->BindAction(ControllerButton::ArrowUp, ButtonState::ButtonDown, &MoveUpRight);
	QBertInput->BindAction(ControllerButton::ArrowLeft, ButtonState::ButtonDown, &MoveUpLeft);
	QBertInput->BindAction(ControllerButton::ArrowRight, ButtonState::ButtonDown, &MoveDownRight);
}