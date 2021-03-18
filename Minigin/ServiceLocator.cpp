#include "MiniginPCH.h"
#include "ServiceLocator.h"

SoundSystem* ServiceLocator::ss_default_instance = new Logging_SoundSystem{};
SoundSystem* ServiceLocator::ss_instance = ss_default_instance;