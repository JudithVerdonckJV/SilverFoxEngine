#pragma once
#include "Scene.h"

class ButtonComponent;

class MainMenu : public fox::Scene
{
public:
	MainMenu() = default;
	~MainMenu() = default;

	virtual void LoadScene() override;
	virtual void Update(float dt) override;
	virtual void EnterScene() override;

private:
	ButtonComponent* m_pSinglePlayerButton;
	ButtonComponent* m_pVersusButton;
	ButtonComponent* m_pCoopButton;
};