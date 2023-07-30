#include "bapch.h"
#include "App.h"

#include "Log.h"

App::App(const std::string& name)
	: m_Name(name)
{
	Init();
}

App::~App()
{
	Terminate();
}

void App::Run()
{
	sf::Image image;
	while (m_Window.isOpen())
	{
		sf::Event event;
		while (m_Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_Window.close();
		}		
	}	
}

void App::Init()
{
	Log::Init();

	BA_LOG_INFO("Initializing {} App.", m_Name);

	m_Window.create(sf::VideoMode(1280, 720), m_Name, sf::Style::Default);
}

void App::Terminate()
{
	BA_LOG_INFO("Terminating {} App.", m_Name);
}
