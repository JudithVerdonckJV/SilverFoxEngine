#include "MiniginPCH.h"
#include "SilverFoxEngine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

using namespace std;
using namespace std::chrono;

void fox::SilverFoxEngine::Initialize()
{
	m_msPerUpdate = 16.f/1000.f;
	
	InitSDL();
}

void fox::SilverFoxEngine::LoadGame() const
{
	GameObject* background{ new GameObject{} };
	IComponent* backgroundTexture{ new TextureRender{ "background.jpg"} };
	background->AddComponent(backgroundTexture);

	GameObject* DAE{ new GameObject };
	DAE->GetComponent<Transform>(fox::IComponent::ComponentID::Transform)->SetPosition(216.f, 180.f);
	IComponent* DAETexture{ new TextureRender{"logo.png"} };
	DAE->AddComponent(DAETexture);

	GameObject* text{ new GameObject{} };
	text->GetComponent<Transform>(fox::IComponent::ComponentID::Transform)->SetPosition(80.f, 20.f);
	IComponent* textFont{ new FontRender{"Lingua.otf", "Programming 4 Assignment"} };
	text->AddComponent(textFont);

	GameObject* fps{ new GameObject{} };
	IComponent* fpsRender{ new FPS{"Lingua.otf"} };
	fps->AddComponent(fpsRender);

	SceneManager& sm{ SceneManager::GetInstance() };
	std::string scene1{ "Scene1" };
	sm.AddScene(scene1);
	sm.AddObjectToScene(scene1, background);
	sm.AddObjectToScene(scene1, DAE);
	sm.AddObjectToScene(scene1, text);
	sm.AddObjectToScene(scene1, fps);
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
			lag += deltaTime;

			doContinue = input.ProcessInput();
			while (lag >= m_msPerUpdate)
			{
				sceneManager.Update(m_msPerUpdate);
				lag -= m_msPerUpdate;
			}
			
			renderer.Render();
		}
	}

	Cleanup();
}

void fox::SilverFoxEngine::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
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