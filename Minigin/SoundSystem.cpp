#include "MiniginPCH.h"
#include "SoundSystem.h"
#include "../3rdParty/Simple-SDL2-Audio-master/src/audio.c"

PlayMessage Sdl_SoundSystem::pending_[MAX_PENDING]{};
int Sdl_SoundSystem::num_pending_{ 0 };
int Sdl_SoundSystem::head_{ 0 };
int Sdl_SoundSystem::tail_{ 0 };