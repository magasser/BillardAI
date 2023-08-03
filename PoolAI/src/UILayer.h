#pragma once

#include "Layer.h"

class UILayer : public Layer
{
public:
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float deltaTime) override;
	void OnUIRender() override;
	void OnEvent(Event& event) override;
};
