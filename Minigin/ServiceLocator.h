#pragma once
#include "SoundSystem.h"

class ServiceLocator final
{
	static SoundSystem* ss_instance;
	static SoundSystem* ss_default_instance;

public:
	static SoundSystem& GetSoundSystem() { return *ss_instance; };
	static void RegisterSoundSystem(SoundSystem* ss)
	{ 
		if (ss == nullptr) ss_instance = ss_default_instance;
		else ss_instance = ss;
	}
};