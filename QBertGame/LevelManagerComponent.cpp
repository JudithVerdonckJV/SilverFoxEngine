#include "GamePch.h"
#include "LevelManagerComponent.h"

#include "GameObject.h"
#include "PlayFieldComponent.h"
#include "QBert_Behavior.h"
#include "Coily_Behavior.h"
#include "SlickAndSam_Behavior.h"
#include "Ugg_Behavior.h"
#include "Wrongway_Behavior.h"

LevelManagerComponent::LevelManagerComponent(fox::GameObject* owner,
	Coily_Behavior* AICoily, Coily_Behavior* playerCoily, SlickAndSam_Behavior* slick, SlickAndSam_Behavior* sam, Ugg_Behavior* ugg, Wrongway_Behavior* wrongway)
	: IComponent{ owner }
	, m_pAICoily{ AICoily }
	, m_pPlayerCoily{ playerCoily }
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

	, m_CurrentUggTimer{ 0.f }
	, m_MaxUggTimer{ 1.f }

	, m_CurrentWrongwayTimer{ 0.f }
	, m_MaxWrongwayTimer{ 2.f }
{
	if (m_pAICoily) m_pAICoily->Despawn();
	if (m_pPlayerCoily) m_pPlayerCoily->Despawn();
	if (m_pSlick) m_pSlick->Despawn();
	if (m_pSam) m_pSam->Despawn();
	if (m_pUgg) m_pUgg->Despawn();
	if (m_pWrongway) m_pWrongway->Despawn();
}

void LevelManagerComponent::Update(float dt)
{
	if (!m_IsCoilyPlayer && m_pAICoily && !m_pAICoily->GetOwner()->IsActive())
	{
		m_CurrentCoilyTimer += dt;
		if (m_CurrentCoilyTimer > m_MaxCoilyTimer)
		{
			m_CurrentCoilyTimer = 0.f;
			m_pAICoily->Spawn();
		}
	}

	if (m_IsCoilyPlayer && m_pPlayerCoily && !m_pPlayerCoily->GetOwner()->IsActive())
	{
		m_CurrentCoilyTimer += dt;
		if (m_CurrentCoilyTimer > m_MaxCoilyTimer)
		{
			m_CurrentCoilyTimer = 0.f;
			m_pPlayerCoily->Spawn();
		}
	}

	if (m_pSlick && !m_pSlick->GetOwner()->IsActive())
	{
		m_CurrentSlickTimer += dt;
		if (m_CurrentSlickTimer > m_MaxSlickTimer)
		{
			m_CurrentSlickTimer = 0.f;
			m_pSlick->Spawn();
		}
	}

	if (m_pSam && !m_pSam->GetOwner()->IsActive())
	{
		m_CurrentSamTimer += dt;
		if (m_CurrentSamTimer > m_MaxSamTimer)
		{
			m_CurrentSamTimer = 0.f;
			m_pSam->Spawn();
		}
	}

	if (m_pUgg && !m_pUgg->GetOwner()->IsActive())
	{
		m_CurrentUggTimer += dt;
		if (m_CurrentUggTimer > m_MaxUggTimer)
		{
			m_CurrentUggTimer = 0.f;
			m_pUgg->Spawn();
		}
	}

	if (m_pWrongway && !m_pWrongway->GetOwner()->IsActive())
	{
		m_CurrentWrongwayTimer += dt;
		if (m_CurrentWrongwayTimer > m_MaxWrongwayTimer)
		{
			m_CurrentWrongwayTimer = 0.f;
			m_pWrongway->Spawn();
		}
	}
}

void LevelManagerComponent::DespawnAll()
{
	if (m_pAICoily) m_pAICoily->Despawn();
	if (m_pPlayerCoily) m_pPlayerCoily->Despawn();
	if (m_pSlick) m_pSlick->Despawn();
	if (m_pSam) m_pSam->Despawn();
	if (m_pUgg) m_pUgg->Despawn();
	if (m_pWrongway) m_pWrongway->Despawn();

	m_CurrentCoilyTimer = 0.f;
	m_CurrentSlickTimer = 0.f;
	m_CurrentSamTimer = 0.f;
	m_CurrentUggTimer = 0.f;
	m_CurrentWrongwayTimer = 0.f;
}

void LevelManagerComponent::CoilyIsPlayer(bool isPlayer)
{
	m_IsCoilyPlayer = isPlayer;
}