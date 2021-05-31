#include "MiniginPCH.h"
#include "LevelManagerComponent.h"

#include "GameObject.h"
#include "PlayFieldComponent.h"
#include "QBert_Behavior.h"
#include "Coily_Behavior.h"
#include "SlickAndSam_Behavior.h"
#include "Ugg_Behavior.h"
#include "Wrongway_Behavior.h"

LevelManagerComponent::LevelManagerComponent(fox::GameObject* owner, PlayFieldComponent* playfield,
	QBert_Behavior* qbert, Coily_Behavior* coily, SlickAndSam_Behavior* slick, SlickAndSam_Behavior* sam, Ugg_Behavior* ugg, Wrongway_Behavior* wrongway)
	: IComponent{ owner }
	, m_pPlayfield{ playfield }
	, m_pQBert{ qbert }
	, m_pCoily{ coily }
	, m_pSlick{ slick }
	, m_pSam{ sam }
	, m_pUgg{ ugg }
	, m_pWrongway{ wrongway }

	, m_CurrentCoilyTimer{ 0.f }
	, m_MaxCoilyTimer{ 3.f }
	
	, m_CurrentSlickTimer{ 0.f }
	, m_MaxSlickTimer{ 7.f }

	, m_CurrentSamTimer{ 0.f }
	, m_MaxSamTimer{ 9.f }
{
	if (m_pCoily) m_pCoily->Despawn();
	if (m_pSlick) m_pSlick->Despawn();
	if (m_pSam) m_pSam->Despawn();
	if (m_pUgg)
	{
		m_pUgg->GetOwner()->SetActive(false);
		m_pUgg->GetOwner()->SetVisibility(false);
	}
	if (m_pWrongway)
	{
		m_pWrongway->GetOwner()->SetActive(false);
		m_pWrongway->GetOwner()->SetVisibility(false);
	}
}

void LevelManagerComponent::Update(float dt)
{
	if (m_pCoily && !m_pCoily->GetOwner()->IsActive())
	{
		m_CurrentCoilyTimer += dt;
		if (m_CurrentCoilyTimer > m_MaxCoilyTimer)
		{
			m_pCoily->Spawn();
		}
	}

	if (m_pSlick && !m_pSlick->GetOwner()->IsActive())
	{
		m_CurrentSlickTimer += dt;
		if (m_CurrentSlickTimer > m_MaxSlickTimer)
		{
			m_pSlick->Spawn();
		}
	}

	if (m_pSam && !m_pSam->GetOwner()->IsActive())
	{
		m_CurrentSamTimer += dt;
		if (m_CurrentSamTimer > m_MaxSamTimer)
		{
			m_pSam->Spawn();
		}
	}
}