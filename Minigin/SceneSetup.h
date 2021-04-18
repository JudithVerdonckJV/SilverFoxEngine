#pragma once
#include "SceneManager.h"

#include "DemoScene.h"

using namespace fox;

class SceneSetup final
{
public:
	SceneSetup()
	{
		SceneManager::GetInstance().AddScene<DemoScene>("Demo");
	};

	~SceneSetup() = default;
};