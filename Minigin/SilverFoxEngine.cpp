#include "MiniginPCH.h"
#include "SilverFoxEngine.h"

#include <chrono>
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "Renderer.h"

#include "utils.h"

#include "GameObject.h"
#include "Scene.h"

#include "SceneSetup.h"

//extern volatile FVector2 WINDOW_SIZE;

using namespace std;
using namespace std::chrono;

void fox::SilverFoxEngine::Initialize()
{
	m_msPerFrame = 1.f / 60.f * 1000.f;
	
	InitSDL();
}

void fox::SilverFoxEngine::LoadGame() const
{
	SceneSetup sceneSetup{};
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

	//std::thread soundThread([]() { while (true) { ServiceLocator::GetSoundSystem().Update(); } });
	//soundThread.detach();

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

	WINDOW_SIZE.x = 640.f;
	WINDOW_SIZE.y = 480.f;

	m_Window = SDL_CreateWindow(
		"SilverFoxEngine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		(int)WINDOW_SIZE.x,
		(int)WINDOW_SIZE.y,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}