#pragma once
#include "Scene.h"

class LevelChange2 : public fox::Scene
{
public:
	LevelChange2() = default;
	~LevelChange2() = default;

	virtual void LoadScene() override;
	virtual void Update(float dt) override;

private:
	float m_CurrentTimer{};
	float m_MaxTimer{};
};