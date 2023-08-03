#include "bapch.h"
#include "GameLayer.h"

#include <SFML/Graphics/Rect.hpp>

#include "B2Utils.h"
#include "Renderer.h"
#include "Settings.h"

void GameLayer::OnAttach()
{
	Settings::ShowHitboxes = true;
}

void GameLayer::OnUpdate(float deltaTime)
{
	m_Game.Update(deltaTime);

	m_Game.Render();
}

void GameLayer::OnEvent(Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
	{
		std::shared_ptr<Ball> cueBall = m_Game.GetCueBall();

		bool isHit = B2Utils::IsInsideBody(cueBall->GetBody(), Renderer::RenderPointToWorldPoint(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)));

		if (isHit)
		{
			cueBall->GetBody()->ApplyLinearImpulseToCenter(Settings::CueBallImpuse, true);
		}
	}
	case sf::Event::MouseMoved:
	{
		b2Vec2 cueBallOrigin = m_Game.GetCueBall()->GetBody()->GetPosition();
		m_Game.SetCueBallTarget(Renderer::RenderPointToWorldPoint({ (float)event.mouseMove.x, (float)event.mouseMove.y }) - cueBallOrigin);		
	}
	break;
	case sf::Event::KeyPressed:
	{
		if (event.key.code == sf::Keyboard::R)
			m_Game.Reset();
	}
	break;
	}
}
