#include "MiniginPCH.h"
#include "DemoScene.h"

#include "TextureComponent.h"
#include "InputComponent.h"
#include "Transform.h"
#include "PlayFieldComponent.h"
#include "GridMovementComponent.h"
#include "QBert_Behavior.h"
#include "Ugg_Behavior.h"
#include "Wrongway_Behavior.h"

#include "Actions.h"
#include "Enums.h"

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

	//PLAYER - QBERT
	GameObject* QBertObject{ new GameObject{this} };
	TextureComponent* qbertTexture = new TextureComponent{QBertObject, "QBertDownLeft.png"};
	qbertTexture->SetPivot(0.5f, 1.3f);
	GridMovementComponent* gridMovement{ new GridMovementComponent{ QBertObject, playfieldComponent } };
	InputComponent* QBertInput{ new InputComponent{QBertObject} };
	QBertObject->SetUserComponent(gridMovement);
	new QBert_Behavior{ QBertObject, gridMovement };

	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_DOWN, SDL_SCANCODE_S,  ButtonState::ButtonDown, &MoveDownLeft);
	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_UP, SDL_SCANCODE_W,  ButtonState::ButtonDown, &MoveUpRight);
	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_LEFT, SDL_SCANCODE_A, ButtonState::ButtonDown, &MoveUpLeft);
	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_RIGHT, SDL_SCANCODE_D, ButtonState::ButtonDown, &MoveDownRight);

	//UGG
	GameObject* uggObject{ new GameObject{this} };
	TextureComponent* uggTexture{ new TextureComponent{uggObject, "Ugg.png"} };
	uggTexture->SetPivot(-0.2f, 0.f);
	GridMovementComponent* uggGridMovement{ new GridMovementComponent{uggObject, playfieldComponent} };
	new Ugg_Behavior{ uggObject, uggGridMovement };

	//WRONGWAY
	GameObject* wrongwayObject{ new GameObject{this} };
	TextureComponent* wrongwaytexture{ new TextureComponent{wrongwayObject, "Wrongway.png"} };
	wrongwaytexture->SetPivot(1.2f, 0.f);
	GridMovementComponent* wrongwayGridMovement{ new GridMovementComponent{wrongwayObject, playfieldComponent} };
	new Wrongway_Behavior{ wrongwayObject, wrongwayGridMovement };
}