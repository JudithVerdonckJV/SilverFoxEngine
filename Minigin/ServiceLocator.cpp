#include "MiniginPCH.h"
#include "ServiceLocator.h"

SoundSystem* ServiceLocator::ss_default_instance = new SDLSoundSystem{};
SoundSystem* ServiceLocator::ss_instance = ss_default_instance;