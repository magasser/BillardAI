#include "bapch.h"
#include "App.h"

#include "Log.h"
#include "UILayer.h"
#include "GameLayer.h"

App* App::s_Instance = nullptr;

App::App(const std::string& name)
	: m_Name(name)
{
	s_Instance = this;

	Init();

	m_Layers.AddLayer(std::make_shared<GameLayer>());
	m_Layers.AddLayer(std::make_shared<UILayer>());
}

App::~App()
{
	Terminate();
}

void App::Run()
{
	sf::Clock frameClock;

	while (m_Window.isOpen())
	{
		m_Window.clear(sf::Color(0x00006EFF));

		Event event;
		while (m_Window.pollEvent(event))
		{
			for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
			{
				if (event.Handled)
					break;

				(*it)->OnEvent(event);
			}

			if (event.Handled)
				continue;

			if (event.type == sf::Event::Closed)
				m_Window.close();
		}

		for (const auto& layer : m_Layers)
		{
			sf::Time deltaTime = frameClock.restart();
			layer->OnUpdate(deltaTime.asSeconds());
		}

		for (const auto& layer : m_Layers)
		{
			layer->OnUIRender();
		}	

		m_Window.display();
	}	
}

void App::Init()
{
	Log::Init();

	PA_LOG_INFO("Initializing {} App.", m_Name);

	m_Window.create(sf::VideoMode(1536, 864), m_Name, sf::Style::Default);
	m_Window.setVerticalSyncEnabled(true);
}

void App::Terminate()
{
	PA_LOG_INFO("Terminating {} App.", m_Name);
}
