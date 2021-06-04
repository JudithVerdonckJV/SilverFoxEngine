#include "MiniginPCH.h"
#include "ButtonComponent.h"
#include "GameObject.h"

#include "Renderer.h"

ButtonComponent::ButtonComponent(fox::GameObject* owner, int w, int h)
	:IComponent{ owner }
	, m_Rectangle{}
	, m_NormalColor{}
	, m_HoveredColor{}
	, m_UsedColor{}
{
	m_Rectangle.x = (int)m_Owner->GetLocation().x;
	m_Rectangle.y = (int)m_Owner->GetLocation().y;
	m_Rectangle.w = w;
	m_Rectangle.h = h;
}

void ButtonComponent::Render() const
{
	SDL_SetRenderDrawColor(fox::Renderer::GetInstance().GetSDLRenderer(), 
		m_UsedColor.r, m_UsedColor.g, m_UsedColor.b, m_UsedColor.a);
	SDL_RenderFillRect(fox::Renderer::GetInstance().GetSDLRenderer(), &m_Rectangle);
}

bool ButtonComponent::IsHovered()
{
	int x{};
	int y{};

	SDL_GetMouseState(&x, &y);

	if (x > m_Rectangle.x && x < m_Rectangle.x + m_Rectangle.w &&
		y > m_Rectangle.y && y <m_Rectangle.y + m_Rectangle.h)
	{
		m_UsedColor = m_HoveredColor;
		return true;
	}
	
	m_UsedColor = m_NormalColor;
	return false;
}

bool ButtonComponent::IsClicked()
{
	bool isHovered = IsHovered();
	
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) &&
		isHovered)
	{
		return true;
	}
	return false;
}

void ButtonComponent::SetNormalColor(SDL_Color color)
{
	m_NormalColor = color;
}

void ButtonComponent::SetHoveredColor(SDL_Color color)
{
	m_HoveredColor = color;
}