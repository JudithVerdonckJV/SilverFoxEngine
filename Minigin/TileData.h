#pragma once
#include "IComponent.h"
#include "Enums.h"

namespace fox
{
	class GameObject;
}

class TileData : public fox::IComponent
{
public:
	TileData(fox::GameObject* owner);
	~TileData() = default;

	ETileType Type;
	bool IsInFinalStage;
};

