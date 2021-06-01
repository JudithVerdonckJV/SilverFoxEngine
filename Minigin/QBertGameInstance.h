#pragma once
#include "Singleton.h"

class ScoreObserver;

class QBertGameInstance final : public fox::Singleton<QBertGameInstance>
{
public:
	~QBertGameInstance() = default;

	int Health;
	int Score;

private:
	friend class fox::Singleton<QBertGameInstance>;
	QBertGameInstance();
};

