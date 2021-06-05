#include "MiniginPCH.h"
#include "SDLSoundSystem.h"
#include <SDL.h>

#include "..\3rdParty\Simple-SDL2-Audio-master\src\audio.c"

PlayMessage SDLSoundSystem::pending_[MAX_PENDING]{};
int SDLSoundSystem::num_pending_{ 0 };
int SDLSoundSystem::head_{ 0 };
int SDLSoundSystem::tail_{ 0 };

SDLSoundSystem::SDLSoundSystem()
	: m_Path{ "../Data/" }
{	
	_putenv("SDL_AUDIODRIVER=DirectSound");
	SDL_Init(SDL_INIT_AUDIO);
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
	auto it = m_SoundMap.find(id);
	if (it == m_SoundMap.end()) return;
	
	if (!m_bMute)
	{
		assert((tail_ + 1) % MAX_PENDING != head_);

		pending_[tail_].id = id;
		pending_[tail_].volume = (int)volume;
		tail_ = (tail_ + 1) % MAX_PENDING;


		for (int i{ head_ }; i != tail_; i = (i + 1) % MAX_PENDING)
		{
			if (pending_[(unsigned short)i].id == id)
			{
				pending_[(unsigned short)i].volume = (int)max(volume, pending_[(unsigned int)i].volume);
				return;
			}
		}
	}
}

void SDLSoundSystem::PlayMusic(const sound_id id, const float volume)
{
	auto it = m_SoundMap.find(id);
	if (it == m_SoundMap.end()) return;
	
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

void SDLSoundSystem::AddSound(sound_id id, const char* filePath)
{
	auto it = m_SoundMap.find(id);
	if (it != m_SoundMap.end()) return;
	
	std::string fullPath{ m_Path + filePath };

	Audio* sound = createAudio(fullPath.c_str(), 0, SDL_MIX_MAXVOLUME / 2);
	m_SoundMap.insert(soundPair{ id, sound });
}