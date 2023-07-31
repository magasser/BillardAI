#include "bapch.h"
#include "Game.h"

#include "Renderer.h"

static b2CircleShape CreateCircle(b2Vec2 position, float radius)
{
	b2CircleShape circle;
	circle.m_p.Set(position.x, position.y);
	circle.m_radius = radius;
	return circle;
}

static b2Body* CreateRectBody(b2World& world, b2Vec2 position, float width, float height)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape staticRect;
	staticRect.SetAsBox(width, height);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticRect;
	fixtureDef.density = 1000.0f;
	fixtureDef.friction = 1000.0f;

	body->CreateFixture(&fixtureDef);
}

Game::Game()
	: m_HitboxEnabled(false)
{
	Init();
}

Game::~Game()
{
	Terminate();
}

void Game::Update(float deltaTime)
{
	const int32_t velocityIterations = 6;
	const int32_t positionIterations = 2;

	m_World->Step(deltaTime, velocityIterations, positionIterations);
}

void Game::Render() const
{
	m_Table->Render();

	m_CueBall->Render();

	for (const auto& ball : m_Balls)
		ball->Render();

	if (m_HitboxEnabled)
	{
		Renderer::DrawWorldHitboxes(m_World);
	}
}

void Game::Reset() {}

void Game::Init()
{
	m_World = std::make_shared<b2World>(b2Vec2_zero);

	m_Table = std::make_shared<Table>(m_World);

	m_CueBall = std::make_shared<Ball>(m_World, 0);

	m_Balls.reserve(15);
	for (uint8_t i = 1; i <= 15; ++i)
		m_Balls.push_back(std::make_shared<Ball>(m_World, i));
}

void Game::Terminate() {}
