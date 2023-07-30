#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class App
{
public:
	App(const std::string& name);
	~App();

	void Run();

private:
	void Init();
	void Terminate();

private:
	std::string m_Name;
	sf::Window m_Window;
};
