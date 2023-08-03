#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "LayerList.h"

class App
{
public:
	App(const std::string& name);
	App(const App& other) = delete;
	~App();

	void Run();

	static sf::RenderWindow& GetWindow() { return s_Instance->m_Window; }
	static App& Get() { return *s_Instance; }

private:
	void Init();
	void Terminate();

private:
	std::string m_Name;
	sf::RenderWindow m_Window;
	LayerList m_Layers;

	static App* s_Instance;
};
