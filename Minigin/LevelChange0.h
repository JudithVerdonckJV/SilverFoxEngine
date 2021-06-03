#pragma once
#include "Scene.h"

class LevelChange0 : public fox::Scene
{
public:
	LevelChange0() = default;
	~LevelChange0() = default;

	virtual void LoadScene() override;
	virtual void Update(float dt) override;

private:
	float m_CurrentTimer{};
	float m_MaxTimer{};
};