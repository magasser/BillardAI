#include "bapch.h"
#include "Game.h"

#include "Renderer.h"
#include "Settings.h"

#if PA_DEBUG
#define RENDER_HITBOXES(enabled, world) { if (enabled) { ::Renderer::DrawWorldHitboxes(world); } }
#else
#define RENDER_HITBOXES(enabled, world)
#endif

static void SetBodyPosition(b2Body* body, b2Vec2 position)
{
	body->SetTransform(position, body->GetAngle());
}

static void SetBodyAngle(b2Body* body, float angle)
{
	body->SetTransform(body->GetPosition(), angle);
}

static void ResetBodyPosition(b2Body* body, b2Vec2 position)
{
	body->SetLinearVelocity(b2Vec2_zero);
	body->SetAngularVelocity(0);
	SetBodyPosition(body, position);
}

static void ShuffleBalls(std::vector<std::shared_ptr<Ball>>& balls)
{
	static std::random_device device;
	static std::default_random_engine engine(device());

	std::shuffle(balls.begin(), balls.end(), engine);
}

void Game::Update(float deltaTime)
{
	constexpr float delta = 1.0f / 60.0f;
	constexpr int32_t velocityIterations = 6;
	constexpr int32_t positionIterations = 2;

	m_World->Step(delta, velocityIterations, positionIterations);

	switch (m_State)
	{
	case GameState::Running: { }
	break;
	case GameState::WaitPlayer:
	{
		UpdateCue();
	}
	break;
	}
}

void Game::Render() const
{
	m_Table->Render();

	for (const auto& pair : m_Balls)
		pair.second->Render();

	if (m_State == GameState::WaitPlayer)
		m_Cue->Render();

	RENDER_HITBOXES(Settings::ShowHitboxes, m_World);

	Renderer::DrawDebugRay(m_Balls.at(CUE_BALL)->GetBody()->GetPosition(), Settings::CueBallImpuse, 0.1f);
	Renderer::DrawDebugRay(m_Balls.at(CUE_BALL)->GetBody()->GetPosition(), m_CueBallTarget, 1.0f, sf::Color::White);
}

void Game::Reset()
{
	constexpr uint32_t solidAndStripesCount = 14;
	constexpr float ballXOffset = BALL_DIAMETER;
	constexpr float ballYOffset = BALL_RADIUS;

	const b2Vec2 headSpot = m_Table->GetHeadSpot();
	const b2Vec2 footSpot = m_Table->GetFootSpot();

	ResetBodyPosition(m_Balls.at(CUE_BALL)->GetBody(), headSpot);

	std::vector<std::shared_ptr<Ball>> solids;
	std::vector<std::shared_ptr<Ball>> stripes;

	for (auto& ball : m_Balls)
	{
		ball.second->SetEnabled(true);

		const uint32_t ballNumber = ball.second->GetNumber();
		if (ballNumber > 0 && ballNumber < 8)
		{
			solids.push_back(ball.second);
		}
		else if (ballNumber > 8)
		{
			stripes.push_back(ball.second);
		}
	}

	ShuffleBalls(solids);
	ShuffleBalls(stripes);

	ResetBodyPosition(solids[0]->GetBody(), footSpot);

	ResetBodyPosition(stripes[0]->GetBody(), b2Vec2(footSpot.x - ballXOffset, footSpot.y - ballYOffset));
	ResetBodyPosition(solids[1]->GetBody(), b2Vec2(footSpot.x - ballXOffset, footSpot.y + ballYOffset));

	ResetBodyPosition(stripes[1]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 2, footSpot.y - ballYOffset * 2));
	ResetBodyPosition(m_Balls[8]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 2, footSpot.y));
	ResetBodyPosition(solids[2]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 2, footSpot.y + ballYOffset * 2));

	ResetBodyPosition(stripes[2]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 3, footSpot.y - ballYOffset * 3));
	ResetBodyPosition(solids[3]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 3, footSpot.y - ballYOffset));
	ResetBodyPosition(stripes[3]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 3, footSpot.y + ballYOffset));
	ResetBodyPosition(solids[4]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 3, footSpot.y + ballYOffset * 3));

	ResetBodyPosition(stripes[4]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 4, footSpot.y - ballYOffset * 4));
	ResetBodyPosition(solids[5]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 4, footSpot.y - ballYOffset * 2));
	ResetBodyPosition(stripes[5]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 4, footSpot.y));
	ResetBodyPosition(solids[6]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 4, footSpot.y + ballYOffset * 2));
	ResetBodyPosition(stripes[6]->GetBody(), b2Vec2(footSpot.x - ballXOffset * 4, footSpot.y + ballYOffset * 4));
}

void Game::Init()
{
	constexpr uint32_t totalBallCount = 16;
	constexpr uint32_t coloredBallCount = 15;

	m_World = std::make_shared<b2World>(b2Vec2_zero);

	m_World->SetContactListener(&m_ContactListener);

	m_Cue = std::make_shared<Cue>(m_World);
	m_Table = std::make_shared<Table>(m_World);

	m_Balls.reserve(totalBallCount);
	for (uint8_t i = 0; i <= coloredBallCount; ++i)
		m_Balls[i] = std::make_shared<Ball>(m_World, i);

	Reset();

	m_State = GameState::WaitPlayer;
}

void Game::Terminate() {}

void Game::UpdateCue()
{
	static float cueCenterDistance = m_Balls.at(CUE_BALL)->GetRadius() + m_Cue->GetLength() / 2;

	b2Vec2 cueBallCenter = m_Balls.at(CUE_BALL)->GetBody()->GetPosition();
	b2Vec2 cuePosition = -m_CueBallTarget;
	cuePosition.Normalize();
	cuePosition *= cueCenterDistance;
	cuePosition += cueBallCenter;

	b2Vec2 cueDirection = cueBallCenter - cuePosition;
	cueDirection.Normalize();

	float cueAngle = acos(b2Dot(cueDirection, { -1.0f, 0.0f }));

	m_Cue->GetBody()->SetTransform(cuePosition, cueDirection.y < 0.0f ? cueAngle : -cueAngle);
}

void ContactListener::BeginContact(b2Contact* contact)
{
	uintptr_t p1 = contact->GetFixtureA()->GetUserData().pointer;
	uintptr_t p2 = contact->GetFixtureB()->GetUserData().pointer;

	if (!p1 || !p2)
		return;

	GameObject* a = reinterpret_cast<GameObject*>(contact->GetFixtureA()->GetUserData().pointer);
	GameObject* b = reinterpret_cast<GameObject*>(contact->GetFixtureB()->GetUserData().pointer);

	if (!a || !b)
		return;

	Pocket* pocket = dynamic_cast<Pocket*>(a);
	GameObject* other = b;

	if (!pocket)
	{
		pocket = dynamic_cast<Pocket*>(b);
		other = a;
	}

	Ball* ball = dynamic_cast<Ball*>(other);
	if (!pocket || !ball)
		return;

	PA_LOG_INFO("Ball {0} went in pocket.", ball->GetNumber());
}
