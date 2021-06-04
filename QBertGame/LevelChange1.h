#pragma once
#include "Scene.h"
class LevelChange1 : public fox::Scene
{
public:
	LevelChange1() = default;
	~LevelChange1() = default;

	virtual void LoadScene() override;
	virtual void Update(float dt) override;

private:
	float m_CurrentTimer{};
	float m_MaxTimer{};
};