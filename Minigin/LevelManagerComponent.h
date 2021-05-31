#pragma once
#include "IComponent.h"

namespace fox
{
	class GameObject;
}

class PlayFieldComponent;
class QBert_Behavior;
class Coily_Behavior;
class SlickAndSam_Behavior;
class Ugg_Behavior;
class Wrongway_Behavior;

class LevelManagerComponent final : public fox::IComponent
{
public:
	LevelManagerComponent(fox::GameObject* owner, PlayFieldComponent* playfield, QBert_Behavior* qbert, Coily_Behavior* coily, SlickAndSam_Behavior* slick, SlickAndSam_Behavior* sam, Ugg_Behavior* ugg, Wrongway_Behavior* wrongway);
	~LevelManagerComponent() = default;

	virtual void Update(float dt) override;

private:
	PlayFieldComponent* m_pPlayfield;
	QBert_Behavior* m_pQBert;
	Coily_Behavior* m_pCoily;
	SlickAndSam_Behavior* m_pSlick;
	SlickAndSam_Behavior* m_pSam;
	Ugg_Behavior* m_pUgg;
	Wrongway_Behavior* m_pWrongway;

	float m_CurrentCoilyTimer;
	float m_MaxCoilyTimer;

	float m_CurrentSlickTimer;
	float m_MaxSlickTimer;

	float m_CurrentSamTimer;
	float m_MaxSamTimer;

	float m_CurrentUggTimer;
	float m_MaxUggTimer;

	float m_CurrentWrongwayTimer;
	float m_MaxWrongwayTimer;
};