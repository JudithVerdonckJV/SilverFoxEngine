#pragma once
#include "SceneManager.h"

#include "DemoScene.h"

#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

using namespace fox;

class SceneSetup final
{
public:
	SceneSetup()
	{

		SceneManager::GetInstance().AddScene<Level1>("Level1");
		SceneManager::GetInstance().AddScene<Level2>("Level2");
		SceneManager::GetInstance().AddScene<Level3>("Level3");

		SceneManager::GetInstance().SetActiveScene("Level1");
	};

	~SceneSetup() = default;
};