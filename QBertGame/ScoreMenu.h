#pragma once
#include "Scene.h"

class ButtonComponent;

namespace fox
{
	class TextComponent;
}

class ScoreMenu : public fox::Scene
{
public:
	ScoreMenu() = default;
	~ScoreMenu() = default;

	virtual void LoadScene() override;
	virtual void Update(float dt) override;
	virtual void EnterScene() override;

private:
	ButtonComponent* m_pMainMenuButton;
	fox::TextComponent* m_pScore;
};