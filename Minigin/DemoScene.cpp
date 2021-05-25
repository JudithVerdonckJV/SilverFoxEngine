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

	//PLAYER - QBERT
	GameObject* QBertObject{ new GameObject{this} };
	new TextureComponent{QBertObject, "fox.png"};
	GridMovementComponent* gridMovement{ new GridMovementComponent{ QBertObject, playfieldComponent } };
	InputComponent* QBertInput{ new InputComponent{QBertObject} };
	QBertObject->SetUserComponent(gridMovement);

	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_DOWN, SDL_SCANCODE_S,  ButtonState::ButtonDown, &MoveDownLeft);
	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_UP, SDL_SCANCODE_W,  ButtonState::ButtonDown, &MoveUpRight);
	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_LEFT, SDL_SCANCODE_A, ButtonState::ButtonDown, &MoveUpLeft);
	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_RIGHT, SDL_SCANCODE_D, ButtonState::ButtonDown, &MoveDownRight);
}