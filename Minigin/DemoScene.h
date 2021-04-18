#pragma once
#include "Scene.h"

class DemoScene final : public fox::Scene
{
public:
	DemoScene() = default;
	~DemoScene() = default;

	virtual void LoadScene() override;
};