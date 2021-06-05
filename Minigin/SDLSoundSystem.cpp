#include "MiniginPCH.h"
#include "SDLSoundSystem.h"

PlayMessage SDLSoundSystem::pending_[MAX_PENDING]{};
int SDLSoundSystem::num_pending_{ 0 };
int SDLSoundSystem::head_{ 0 };
int SDLSoundSystem::tail_{ 0 };

SDLSoundSystem::SDLSoundSystem()
{
	initAudio();
}

SDLSoundSystem::~SDLSoundSystem()
{
	endAudio();

	for (soundPair& sound : m_SoundMap)
	{
		freeAudio(sound.second);
	}
}

void SDLSoundSystem::PlayEffect(const sound_id id, const float volume)
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
				pending_[(unsigned int)i].volume = (int)max(volume, pending_[(unsigned int)i].volume);
				return;
			}
		}
	}
}

void SDLSoundSystem::PlayMusic(const sound_id id, const float volume)
{
	if (!m_bMute)
	{
		Audio* sound = m_SoundMap[id];
		playMusicFromMemory(sound, (int)volume);
	}
}

void SDLSoundSystem::Update()
{
	if (head_ == tail_) return;
	Audio* sound = m_SoundMap[pending_[head_].id];
	playSoundFromMemory(sound, pending_[head_].volume);
	head_ = (head_ + 1) % MAX_PENDING;
}

void SDLSoundSystem::Mute(bool mute)
{
	m_bMute = mute;
	if (mute) pauseAudio();
	else unpauseAudio();
}

sound_id SDLSoundSystem::AddSound(const char* filePath)
{
	Audio* sound = createAudio(filePath, 0, SDL_MIX_MAXVOLUME / 2);
	m_SoundMap.insert(soundPair{ m_MaxId, sound });
	++m_MaxId;
	return m_MaxId - 1;
}