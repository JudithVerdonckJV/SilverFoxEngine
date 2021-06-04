#pragma once
#include <map>
#include <cassert>
#include "../3rdParty/Simple-SDL2-Audio-master/src/audio.h"

using sound_id = unsigned short;
using soundPair = std::pair<const sound_id, Audio*>;

struct PlayMessage
{
	sound_id id;
	int volume;
};

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

class Sdl_SoundSystem final : public SoundSystem
{
public:
	Sdl_SoundSystem()
	{
		initAudio();
	}

	virtual ~Sdl_SoundSystem()
	{
		endAudio();

		for (soundPair& sound : m_SoundMap)
		{
			freeAudio(sound.second);
		}
	}

	virtual void PlayEffect(const sound_id id, const float volume) override
	{
		if (!m_bMute)
		{
			assert((tail_ + 1) % MAX_PENDING != head_);

			pending_[tail_].id = id;
			pending_[tail_].volume = (int)volume;
			tail_ = (tail_ + 1) % MAX_PENDING;


			for (int i{ head_ }; i != tail_; i = (i + 1) % MAX_PENDING)
			{
				if (pending_[(unsigned int)i].id == id)
				{
					//pending_[(unsigned int)i].volume = (int)max(volume, pending_[(unsigned int)i].volume);
					return;
				}
			}
		}
	}

	virtual void PlayMusic(const sound_id id, const float volume) override
	{
		if (!m_bMute)
		{
			Audio* sound = m_SoundMap[id];
			playMusicFromMemory(sound, (int)volume);
		}
	}

	virtual void Update() override
	{
		if (head_ == tail_) return;
		Audio* sound = m_SoundMap[pending_[head_].id];
		playSoundFromMemory(sound, pending_[head_].volume);
		head_ = (head_ + 1) % MAX_PENDING;
	}

	virtual void Mute(bool mute) override
	{
		m_bMute = mute;
		if (mute) pauseAudio();
		else unpauseAudio();
	}

	virtual sound_id AddSound(const char* filePath) override
	{
		Audio* sound = createAudio(filePath, 0, SDL_MIX_MAXVOLUME / 2);
		m_SoundMap.insert(soundPair{ m_MaxId, sound });
		++m_MaxId;
		return m_MaxId - 1;
	}

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