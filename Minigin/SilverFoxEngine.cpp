#include "MiniginPCH.h"
#include "SilverFoxEngine.h"

#include <chrono>
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Observer.h"
#include "PlayerState.h"
#include "ObserverManager.h"

#include "Actions.h"
#include "ServiceLocator.h"

using namespace std;
using namespace std::chrono;

void fox::SilverFoxEngine::Initialize()
{
	m_msPerFrame = 1.f / 60.f * 1000.f;
	
	InitSDL();
}

void fox::SilverFoxEngine::LoadGame() const
{
	//DEMO
	GameObject* background{ new GameObject{} };
	IComponent* backgroundTexture{ new TextureComponent{ background } };
	static_cast<TextureComponent*>(backgroundTexture)->SetTexture("background.jpg");
	background->AddComponent(backgroundTexture);

	GameObject* DAE{ new GameObject };
	DAE->GetComponent<Transform>()->SetPosition(216.f, 180.f);
	IComponent* DAETexture{ new TextureComponent{ DAE } };
	static_cast<TextureComponent*>(DAETexture)->SetTexture("logo.png");
	DAE->AddComponent(DAETexture);

	GameObject* text{ new GameObject{} };
	text->GetComponent<Transform>()->SetPosition(80.f, 20.f);
	IComponent* textFont{ new TextComponent{ text } };
	static_cast<TextComponent*>(textFont)->SetText("Programming 4 Assignment");
	static_cast<TextComponent*>(textFont)->SetSize(36);
	text->AddComponent(textFont);

	GameObject* fps{ new GameObject{} };
	IComponent* fpsRender{ new FpsComponent{fps} };
	static_cast<FpsComponent*>(fpsRender)->SetSize(24);
	static_cast<FpsComponent*>(fpsRender)->SetColor(200, 200, 30, 255);
	fps->AddComponent(fpsRender);

	//QBERT OBSERVER ASSIGNMENT
	Observer* playerState = new PlayerState{};
	ObserverManager::GetInstance().AddObserver(playerState);

	float playerHealth{ 2.f };

	//player 1
	GameObject* player1{ new GameObject{} };
	player1->GetComponent<Transform>()->SetPosition(216.f, 280.f);
	player1->pSubject->AddObserver(playerState);

	IComponent* UIHealth1{ new TextComponent{player1} };
	static_cast<TextComponent*>(UIHealth1)->SetSize(30);
	static_cast<TextComponent*>(UIHealth1)->SetText("Health is " + to_string((int)playerHealth));
	static_cast<TextComponent*>(UIHealth1)->SetColor(255, 20, 20, 255);
	
	IComponent* health1{ new HealthComponent{player1, playerHealth} };

	IComponent* input1{ new InputComponent{player1} };
	static_cast<InputComponent*>(input1)->BindAction(fox::ControllerButton::ButtonX, fox::ButtonState::ButtonDown, Damage);
	static_cast<InputComponent*>(input1)->BindAction(fox::ControllerButton::ButtonY, fox::ButtonState::ButtonDown, ResetHealth);
	
	player1->AddComponent(input1);
	player1->AddComponent(UIHealth1);
	player1->AddComponent(health1);

	//player 2
	GameObject* player2{ new GameObject{} };
	player2->GetComponent<Transform>()->SetPosition(216.f, 320.f);
	player2->pSubject->AddObserver(playerState);

	IComponent* UIHealth2{ new TextComponent{player2} };
	static_cast<TextComponent*>(UIHealth2)->SetSize(30);
	static_cast<TextComponent*>(UIHealth2)->SetText("Health is " + to_string((int)playerHealth));
	static_cast<TextComponent*>(UIHealth2)->SetColor(255, 20, 20, 255);

	IComponent* health2{ new HealthComponent{player2, playerHealth} };

	IComponent* input2{ new InputComponent{player2} };
	static_cast<InputComponent*>(input2)->BindAction(fox::ControllerButton::ButtonX, fox::ButtonState::ButtonDown, Damage);
	static_cast<InputComponent*>(input2)->BindAction(fox::ControllerButton::ButtonY, fox::ButtonState::ButtonDown, ResetHealth);

	player2->AddComponent(input2);
	player2->AddComponent(UIHealth2);
	player2->AddComponent(health2);

	SceneManager& sm{ SceneManager::GetInstance() };
	std::string scene1{ "Scene1" };
	sm.AddScene(scene1);
	sm.AddObjectToScene(scene1, background);
	sm.AddObjectToScene(scene1, DAE);
	sm.AddObjectToScene(scene1, text);
	sm.AddObjectToScene(scene1, fps);

	sm.AddObjectToScene(scene1, player1);
	sm.AddObjectToScene(scene1, player2);

	//SOUND
	initAudio();
	ServiceLocator::RegisterSoundSystem(new Sdl_SoundSystem{});
	static_cast<InputComponent*>(input1)->BindAction(fox::ControllerButton::ButtonA, fox::ButtonState::ButtonDown, PlayASoundTEST);
}

void fox::SilverFoxEngine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void fox::SilverFoxEngine::Run()
{
	Initialize();

	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		Renderer& renderer{ Renderer::GetInstance() };
		SceneManager& sceneManager { SceneManager::GetInstance() };
		InputManager& input { InputManager::GetInstance()};

		bool doContinue { true };
		auto lastTime{ high_resolution_clock::now() };
		float lag{ 0.0f };

		while (doContinue)
		{                                
			const auto currentTime{ high_resolution_clock::now() };
			float deltaTime{ duration<float>(currentTime - lastTime).count() };
			lastTime = currentTime;
			
			doContinue = input.ProcessInput();

			sceneManager.Update(deltaTime);

			lag += deltaTime;
			while (lag >= m_msPerFrame * 1000.f)
			{
				sceneManager.FixedUpdate(m_msPerFrame);
				lag -= m_msPerFrame;
			}
			
			sceneManager.LateUpdate(deltaTime);

			renderer.Render();

			const auto sleepTime = currentTime + milliseconds((long)m_msPerFrame) - high_resolution_clock::now();
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void fox::SilverFoxEngine::InitSDL()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"SilverFoxEngine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}