#pragma once

#include "Layer.h"
#include "Game.h"

class GameLayer : public Layer
{
public:
	void OnAttach() override;
	void OnUpdate(float deltaTime) override;

private:
	Game m_Game;
};
