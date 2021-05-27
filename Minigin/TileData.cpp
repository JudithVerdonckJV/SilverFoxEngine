#include "MiniginPCH.h"
#include "TileData.h"

TileData::TileData(fox::GameObject* owner)
	: IComponent{ owner }
	, Type{ ETileType::Stage0 }
	, IsInFinalStage{ false }
{
}