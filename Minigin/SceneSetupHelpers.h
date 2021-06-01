#pragma once
#include "SDL.h"

#include "QBert_Behavior.h"
#include "Ugg_Behavior.h"
#include "Wrongway_Behavior.h"
#include "SlickAndSam_Behavior.h"
#include "Coily_Behavior.h"

#include "GameObject.h"
#include "Scene.h"

#include "TextureComponent.h"
#include "InputComponent.h"
#include "PlayFieldComponent.h"
#include "DiscsComponent.h"
#include "RectColliderComponent.h"
#include "SubjectComponent.h"

#include "Actions.h"
#include "ScoreObserver.h"

using namespace fox;

inline QBert_Behavior* CreateQbertObject(Scene* scene, PlayFieldComponent* playfield, DiscsComponent* discs)
{
	GameObject* QBertObject{ new GameObject{ scene } };
	TextureComponent* qbertTexture = new TextureComponent{ QBertObject, "QBertDownLeft.png" };
	qbertTexture->SetPivot(0.5f, 1.3f);
	GridMovementComponent* gridMovement{ new GridMovementComponent{ QBertObject, playfield, discs } };
	InputComponent* QBertInput{ new InputComponent{QBertObject} };
	QBertObject->SetUserComponent(gridMovement);
	QBert_Behavior* qbertBehavior = new QBert_Behavior{ QBertObject, gridMovement };
	RectColliderComponent* qbertColl = new RectColliderComponent{ QBertObject };
	qbertColl->SetDimensions({ 15.f, 15.f });
	qbertColl->SetRelativePosition({ 7.5f, 35.f });
	qbertColl->SetOverlapCallback([](GameObject*) { });

	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_DOWN, SDL_SCANCODE_S, ButtonState::ButtonDown, &MoveDownLeft);
	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_UP, SDL_SCANCODE_W, ButtonState::ButtonDown, &MoveUpRight);
	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_LEFT, SDL_SCANCODE_A, ButtonState::ButtonDown, &MoveUpLeft);
	QBertInput->BindAction(XINPUT_GAMEPAD_DPAD_RIGHT, SDL_SCANCODE_D, ButtonState::ButtonDown, &MoveDownRight);

	return qbertBehavior;
}

inline Ugg_Behavior* CreateUggObject(Scene* scene, PlayFieldComponent* playfield)
{
	GameObject* uggObject{ new GameObject{scene} };
	TextureComponent* uggTexture{ new TextureComponent{uggObject, "Ugg.png"} };
	uggTexture->SetPivot(-0.2f, 0.f);
	GridMovementComponent* uggGridMovement{ new GridMovementComponent{uggObject, playfield, nullptr} };
	Ugg_Behavior* uggBehavior = new Ugg_Behavior{ uggObject, uggGridMovement };
	RectColliderComponent* uggColl = new RectColliderComponent{ uggObject };
	uggColl->SetDimensions({ 15.f, 15.f });
	uggColl->SetRelativePosition({ -10.f, -10.f });
	uggColl->SetOverlapCallback([](GameObject*) { });

	return uggBehavior;
}

inline Wrongway_Behavior* CreateWrongwayObject(Scene* scene, PlayFieldComponent* playfield)
{
	GameObject* wrongwayObject{ new GameObject{scene} };
	TextureComponent* wrongwaytexture{ new TextureComponent{wrongwayObject, "Wrongway.png"} };
	wrongwaytexture->SetPivot(1.2f, 0.f);
	GridMovementComponent* wrongwayGridMovement{ new GridMovementComponent{wrongwayObject, playfield, nullptr} };
	Wrongway_Behavior* wrongwayBehavior = new Wrongway_Behavior{ wrongwayObject, wrongwayGridMovement };
	RectColliderComponent* wrongwayColl = new RectColliderComponent{ wrongwayObject };
	wrongwayColl->SetDimensions({ 15.f, 15.f });
	wrongwayColl->SetRelativePosition({ 30.f, -10.f });
	wrongwayColl->SetOverlapCallback([](GameObject*) { });

	return wrongwayBehavior;
}

inline SlickAndSam_Behavior* CreateSlickObject(Scene* scene, PlayFieldComponent* playfield, ScoreObserver* scoreObserver)
{
	GameObject* samObject{ new GameObject{scene} };
	TextureComponent* samtexture{ new TextureComponent{samObject, "Sam.png"} };
	samtexture->SetPivot(0.5f, 1.3f);
	GridMovementComponent* samGridMovement{ new GridMovementComponent{samObject, playfield, nullptr} };
	SlickAndSam_Behavior* slickBehavior = new SlickAndSam_Behavior{ samObject, samGridMovement };
	RectColliderComponent* samColl = new RectColliderComponent{ samObject };
	samColl->SetDimensions({ 15.f, 15.f });
	samColl->SetRelativePosition({ 10.f, 35.f });
	samColl->SetOverlapCallback([](GameObject*) { });

	SubjectComponent* subject{ new SubjectComponent{samObject} };
	subject->AddObserver(scoreObserver);

	return slickBehavior;
}

inline SlickAndSam_Behavior* CreateSamObject(Scene* scene, PlayFieldComponent* playfield, ScoreObserver* scoreObserver)
{
	GameObject* slickObject{ new GameObject{scene} };
	TextureComponent* slicktexture{ new TextureComponent{slickObject, "Slick.png"} };
	slicktexture->SetPivot(0.5f, 1.3f);
	GridMovementComponent* slickGridMovement{ new GridMovementComponent{slickObject, playfield, nullptr} };
	SlickAndSam_Behavior* samBehavior = new SlickAndSam_Behavior{ slickObject, slickGridMovement };
	RectColliderComponent* slickColl = new RectColliderComponent{ slickObject };
	slickColl->SetDimensions({ 15.f, 15.f });
	slickColl->SetRelativePosition({ 10.f, 35.f });
	slickColl->SetOverlapCallback([](GameObject*) { });

	SubjectComponent* subject{ new SubjectComponent{slickObject} };
	subject->AddObserver(scoreObserver);

	return samBehavior;
}

inline Coily_Behavior* CreateCoilyObject(Scene* scene, PlayFieldComponent* playfield, ScoreObserver* scoreObserver)
{
	GameObject* coilyObject{ new GameObject{scene} };
	TextureComponent* coilytexture{ new TextureComponent{coilyObject, "Coily_Egg.png"} };
	coilytexture->SetPivot(0.5f, 1.3f);
	GridMovementComponent* coilyGridMovement{ new GridMovementComponent{coilyObject, playfield, nullptr} };
	Coily_Behavior* coilyBehavior = new Coily_Behavior{ coilyObject, coilyGridMovement };
	RectColliderComponent* coilyColl = new RectColliderComponent{ coilyObject };
	coilyColl->SetDimensions({ 15.f, 15.f });
	coilyColl->SetRelativePosition({ 10.f, 35.f });
	coilyColl->SetOverlapCallback([](GameObject*) { });

	SubjectComponent* subject{ new SubjectComponent{coilyObject} };
	subject->AddObserver(scoreObserver);

	return coilyBehavior;
}