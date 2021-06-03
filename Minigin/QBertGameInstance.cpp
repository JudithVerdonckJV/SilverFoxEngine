#include "MiniginPCH.h"
#include "QBertGameInstance.h"
#include "UI.h"

QBertGameInstance::QBertGameInstance()
	: m_Health{}
	, m_Score{}
	, m_pUI{}
{
}

void QBertGameInstance::ChangeHealth(int amount)
{
	m_Health += amount;
	m_pUI->UpdateHealth(m_Health);
}

int QBertGameInstance::GetHealth() const
{
	return m_Health;
}

void QBertGameInstance::ChangeScore(int amount)
{
	m_Score += amount;
	m_pUI->UpdateScore(m_Score);
}

int QBertGameInstance::GetScore() const
{
	return m_Score;
}

void QBertGameInstance::SetUI(UI* ui)
{
	m_pUI = ui;
	m_pUI->UpdateHealth(m_Health);
	m_pUI->UpdateScore(m_Score);
}

void QBertGameInstance::Reset()
{
	m_Score = 0;
	m_Health = 3;
}