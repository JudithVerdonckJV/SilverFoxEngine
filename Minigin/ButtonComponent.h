#pragma once
#include "IComponent.h"
#include <SDL.h>

namespace fox
{
	class GameObject;
}

class ButtonComponent : public fox::IComponent
{
public:
	ButtonComponent(fox::GameObject* owner, int w, int h);
	~ButtonComponent() = default;

	virtual void Render() const override;

	bool IsClicked();

	void SetNormalColor(SDL_Color color);
	void SetHoveredColor(SDL_Color color);

private:
	SDL_Rect m_Rectangle;

	SDL_Color m_NormalColor;
	SDL_Color m_HoveredColor;

	SDL_Color m_UsedColor;

	bool IsHovered();
};