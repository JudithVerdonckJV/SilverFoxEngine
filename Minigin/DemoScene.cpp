#include "MiniginPCH.h"
#include "DemoScene.h"

#include "TextureComponent.h"
#include "InputComponent.h"
#include "Transform.h"

#include "Actions.h"

using namespace fox;

void DemoScene::LoadScene()
{
	//BACKGROUND
	GameObject* background{ new GameObject{this} };
	IComponent* backgroundTexture{ new TextureComponent{ background } };
	static_cast<TextureComponent*>(backgroundTexture)->SetTexture("background.jpg");

	//LOGO
	GameObject* DAE{ new GameObject {background} };
	IComponent* DAETexture{ new TextureComponent{ DAE } };
	static_cast<TextureComponent*>(DAETexture)->SetTexture("logo.png");

	//FOX
	GameObject* fox{ new GameObject {this} };
	fox->SetTransform({50.f, 50.f}, {0.f, 0.f}, {1.f, 1.f} );
	IComponent* foxTexture{ new TextureComponent{fox} };
	static_cast<TextureComponent*>(foxTexture)->SetTexture("fox.png");
	//IComponent* foxInput(new InputComponent{ fox });
	//static_cast<InputComponent*>(foxInput)->BindAction(fox::ControllerButton::ButtonA, fox::ButtonState::ButtonDown, MoveRight);
}