#pragma once
#include <iostream>
//#include <SDL.h>
#include "../3rdParty/Simple-SDL2-Audio-master/src/audio.h"
//#include "../3rdParty/Simple-SDL2-Audio-master/src/audio.c"

using namespace std;
using sound_id = unsigned short;

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(const sound_id id, const float volume) = 0;
};

class Sdl_SoundSystem final : public SoundSystem
{
public:
	virtual void Play(const sound_id , const float )
	{
		if (!m_bMute)
		{
			playSound("./Data/Sound/PageFlip.wav", 100); // doesnt work. Nice. Fucking library.
		}
	}

	void Mute(bool mute)
	{
		m_bMute = mute;
	}

private:
    bool m_bMute{ false };
};

class Logging_SoundSystem final : public SoundSystem
{
	virtual void Play(const sound_id id, const float volume)
	{
		cout << "Sound logger: playing " << id << "at volume " << volume << endl;
		cout << "Did you forget to assign an SDL soundsystem to the service locator?\n";
	}
};