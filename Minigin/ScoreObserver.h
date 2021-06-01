#pragma once
#include "IObserver.h"

namespace fox
{
	class GameObject;
}

class QBertGameInstance;

class ScoreObserver : public fox::IObserver
{
public:
	ScoreObserver();
	~ScoreObserver() = default;

	virtual void OnNotify(fox::GameObject* pSubject, int event) override;

private:
	QBertGameInstance* m_pGameInstance;
};