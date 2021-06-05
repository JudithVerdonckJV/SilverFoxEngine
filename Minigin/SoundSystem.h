#pragma once
#include <cassert>
using sound_id = unsigned short;

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void PlayEffect(const sound_id id, const float volume) = 0;
	virtual void PlayMusic(const sound_id id, const float volume) = 0;
	virtual void Update() = 0;

	virtual void Mute(bool mute) = 0;
	virtual sound_id AddSound(const char* filePath) = 0;
};