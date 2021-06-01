#include "MiniginPCH.h"
#include "IObserver.h"
#include "ObserverManager.h"

fox::IObserver::IObserver()
{
	ObserverManager::GetInstance().AddObserver(this);
}