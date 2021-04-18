#pragma once
struct SDL_Window;

namespace fox
{
	class SilverFoxEngine
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

	private:
		float m_msPerFrame{ };
		SDL_Window* m_Window{};

		void InitSDL();
	};
}