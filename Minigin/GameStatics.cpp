#include "MiniginPCH.h"
#include "GameStatics.h"
#include "GameObject.h"

FVector2 fox::GameStatics::WINDOW_SIZE{};
std::vector<fox::GameObject*> fox::GameStatics::m_Players{};

fox::GameObject* fox::GameStatics::GetPlayerObject(size_t index)
{
	if (index < m_Players.size() && index >= 0) return m_Players[index];
	else return nullptr;
}