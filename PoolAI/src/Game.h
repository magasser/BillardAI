#pragma once

#include "Ball.h"
#include "Table.h"

class Game
{
public:
	Game();
	~Game();

	void Update(float deltaTime);
	void Render() const;
	void Reset();
	void SetHitboxEnabled(bool enabled) { m_HitboxEnabled = enabled; }

	inline std::shared_ptr<Table> GetTable() const { return m_Table; }
	inline std::shared_ptr<Ball> GetCueBall() const { return m_CueBall; }
	inline const std::vector<std::shared_ptr<Ball>>& GetBalls() const { return m_Balls; }

private:
	void Init();
	void Terminate();

private:
	bool m_HitboxEnabled;
	std::shared_ptr<b2World> m_World;

	std::shared_ptr<Table> m_Table;
	std::shared_ptr<Ball> m_CueBall;
	std::vector<std::shared_ptr<Ball>> m_Balls;
};
