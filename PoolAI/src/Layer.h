#pragma once

#include "Event.h"

class Layer
{
public:
	Layer(const std::string& name = "Layer") : m_Name(name) {}
	virtual ~Layer() {}

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnUIRender() {}
	virtual void OnEvent(Event& event) {}

	const std::string& GetName() const { return m_Name; }

protected:
	std::string m_Name;
};
