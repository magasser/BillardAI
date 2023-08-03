#pragma once

#include "Cue.h"
#include "Ball.h"
#include "Table.h"

#define CUE_BALL 0

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;
};

enum class GameState
{
	Unknown = 0,
	WaitPlayer,
	Running,
};

class Game
{
public:

public:
	Game() : m_State(GameState::Unknown), m_CueBallTarget({-1.0f, 0.0f}) { Init(); }
	Game(const Game& other) = delete;
	~Game() { Terminate(); }

	void Update(float deltaTime);

	void Render() const;
	void Reset();

	inline void SetCueBallTarget(b2Vec2 target) { m_CueBallTarget = target; }

	inline GameState GetState() const { return m_State; }
	inline std::shared_ptr<b2World> GetWorld() const { return m_World; }
	inline std::shared_ptr<Cue> GetCue() const { return m_Cue; }
	inline std::shared_ptr<Table> GetTable() const { return m_Table; }
	inline std::shared_ptr<Ball> GetCueBall() const { return m_Balls.at(CUE_BALL); }
	inline const std::unordered_map<uint32_t, std::shared_ptr<Ball>>& GetBalls() const { return m_Balls; }

private:
	void Init();
	void Terminate();

	void UpdateCue();

private:
	GameState m_State;
	ContactListener m_ContactListener;
	std::shared_ptr<b2World> m_World;
	std::shared_ptr<Cue> m_Cue;
	std::shared_ptr<Table> m_Table;
	std::unordered_map<uint32_t, std::shared_ptr<Ball>> m_Balls;

	b2Vec2 m_CueBallTarget;
};
