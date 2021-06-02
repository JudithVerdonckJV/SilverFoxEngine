#pragma once
#include "Scene.h"

class PlayFieldComponent;
class DiscsComponent;
class QBert_Behavior;
class LevelManagerComponent;
class UI;

class QBertGameInstance;

class Level2 final : public fox::Scene
{
public:
	Level2() = default;
	~Level2() = default;

	virtual void LoadScene() override;
	virtual void EnterScene() override;
	virtual void Update(float dt) override;

private:
	PlayFieldComponent* m_pPlayfield;
	DiscsComponent* m_pDiscs;
	QBert_Behavior* m_pQBert;
	LevelManagerComponent* m_pLevelManager;
	UI* m_pUI;

	QBertGameInstance* m_pGameInstance;
};