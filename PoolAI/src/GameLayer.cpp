#include "bapch.h"
#include "GameLayer.h"

#include <SFML/Graphics/Rect.hpp>

#include "Renderer.h"

void GameLayer::OnAttach()
{
	m_Game.SetHitboxEnabled(true);
}

void GameLayer::OnUpdate(float deltaTime)
{
	m_Game.Update(deltaTime);

	m_Game.Render();
}
