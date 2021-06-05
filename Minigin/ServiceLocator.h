#pragma once
#include "SDLSoundSystem.h"

class ServiceLocator final
{
	static SoundSystem* ss_instance;
	static SoundSystem* ss_default_instance;

public:
	~ServiceLocator()
	{
		if (ss_instance) delete ss_instance;
		if (ss_default_instance) delete ss_default_instance;
	}

	static SoundSystem& GetSoundSystem() { return *ss_instance; };
	static void RegisterSoundSystem(SoundSystem* ss)
	{ 
		if (ss_instance != ss_default_instance) delete ss_instance;
		if (ss == nullptr) ss_instance = ss_default_instance;
		else ss_instance = ss;
	}
};