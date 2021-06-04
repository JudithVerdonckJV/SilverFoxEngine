#pragma once
#include "SceneManager.h"

#include "DemoScene.h"

#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

#include "LevelChange0.h"
#include "LevelChange1.h"
#include "LevelChange2.h"

#include "MainMenu.h"
#include "ScoreMenu.h"

using namespace fox;

class SceneSetup final
{
public:
	SceneSetup()
	{
		SceneManager::GetInstance().AddScene<Level1>("Level1");
		SceneManager::GetInstance().AddScene<Level2>("Level2");
		SceneManager::GetInstance().AddScene<Level3>("Level3");

		SceneManager::GetInstance().AddScene<LevelChange0>("LevelChange0");
		SceneManager::GetInstance().AddScene<LevelChange1>("LevelChange1");
		SceneManager::GetInstance().AddScene<LevelChange2>("LevelChange2");

		SceneManager::GetInstance().AddScene<MainMenu>("MainMenu");
		SceneManager::GetInstance().AddScene<ScoreMenu>("ScoreMenu");

		SceneManager::GetInstance().SetActiveScene("MainMenu");
	};

	~SceneSetup() = default;
};