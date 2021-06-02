#include "MiniginPCH.h"
#include "ScoreObserver.h"

#include "GameObject.h"
#include "QBertGameInstance.h"
#include "Enums.h"

ScoreObserver::ScoreObserver()
	: IObserver{}
	, m_pGameInstance{}
{
	m_pGameInstance = &QBertGameInstance::GetInstance();
}

void ScoreObserver::OnNotify(fox::GameObject* , int event)
{
	int scoreIncrease{};
	
	switch (EObserverEvents(event))
	{
	case EObserverEvents::CoilyDeath:
		scoreIncrease = 500;
		break;
	case EObserverEvents::SlickSamDeath:
		scoreIncrease = 300;
		break;
	case EObserverEvents::RemainingDisc:
		scoreIncrease = 50;
		break;
	case EObserverEvents::Colorchange:
		scoreIncrease = 25;
		break;
	}

	m_pGameInstance->ChangeScore(scoreIncrease);
}