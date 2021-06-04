#pragma once
#include "Singleton.h"
#include "Enums.h"

class UI;

class QBertGameInstance final : public fox::Singleton<QBertGameInstance>
{
public:
	~QBertGameInstance() = default;

	void ChangeHealth(int amount);
	int GetHealth() const;

	void ChangeScore(int amount);
	int GetScore() const;

	void SetUI(UI* ui);

	void Reset();

	EGameModes GameMode;

private:
	friend class fox::Singleton<QBertGameInstance>;
	QBertGameInstance();

	int m_Health;
	int m_Score;

	UI* m_pUI;
};

