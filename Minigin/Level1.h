#pragma once
#include "Scene.h"

class PlayFieldComponent;
class DiscsComponent;
class QBert_Behavior;
class LevelManagerComponent;

class QBertGameInstance;

class Level1 final : public fox::Scene
{
public:
	Level1() = default;
	~Level1() = default;

	virtual void LoadScene() override;
	virtual void EnterScene() override;
	virtual void Update(float dt) override;

private:
	PlayFieldComponent* m_pPlayfield;
	DiscsComponent* m_pDiscs;
	QBert_Behavior* m_pQBert;
	LevelManagerComponent* m_pLevelManager;

	QBertGameInstance* m_pGameInstance;
};