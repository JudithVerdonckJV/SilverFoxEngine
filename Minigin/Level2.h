#pragma once
#include "Scene.h"

class PlayFieldComponent;
class DiscsComponent;
class QBert_Behavior;
class Coily_Behavior;
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
	QBert_Behavior* m_pQBert1;
	QBert_Behavior* m_pQBert2;
	Coily_Behavior* m_AICoily;
	Coily_Behavior* m_PlayerCoily;
	LevelManagerComponent* m_pLevelManager;
	UI* m_pUI;

	QBertGameInstance* m_pGameInstance;
};