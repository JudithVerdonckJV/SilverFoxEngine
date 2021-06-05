#pragma once
#include "SoundSystem.h"
#include <map>
#include <SDL.h>
#include "..\3rdParty\Simple-SDL2-Audio-master\src\audio.h"
// i know this isnt a good way of including this file, but it is literally the only way that doesnt cause it to crash.
// dont touch


using soundPair = std::pair<const sound_id, Audio*>;

struct PlayMessage
{
	sound_id id;
	int volume;
};

class SDLSoundSystem final : public SoundSystem
{
public:
	SDLSoundSystem();

	virtual ~SDLSoundSystem();

	virtual void PlayEffect(const sound_id id, const float volume) override;

	virtual void PlayMusic(const sound_id id, const float volume) override;

	virtual void Update() override;

	virtual void Mute(bool mute) override;

	virtual sound_id AddSound(const char* filePath) override;

private:
	bool m_bMute{ false };
	sound_id m_MaxId{ 0 };
	std::map<sound_id, Audio*> m_SoundMap{};

	//(event) sound queue
	static const int MAX_PENDING = 16;
	static PlayMessage pending_[MAX_PENDING];
	static int num_pending_;

	static int head_;
	static int tail_;
};

class Logging_SoundSystem final : public SoundSystem
{
	virtual void PlayEffect(const sound_id id, const float volume) override
	{
		if (m_bMute) std::cout << "Sound logger is muted; no audio effect would play.\n";
		else std::cout << "Sound logger: playing effect " << id << "at volume " << volume << std::endl;
	}

	virtual void PlayMusic(const sound_id id, const float volume) override
	{
		if (m_bMute) std::cout << "Sound logger is muted; no music would play.\n";
		else std::cout << "Sound logger: playing music " << id << "at volume " << volume << std::endl;
	}

	virtual void Update() override {};

	virtual void Mute(bool mute) override
	{
		m_bMute = mute;
		std::cout << "Logger was muted.\n";
	}

	virtual sound_id AddSound(const char*) override
	{
		std::cout << "Sound logger will not save any sounds.\n";
		return 0;
	}

private:
	bool m_bMute{ false };
};