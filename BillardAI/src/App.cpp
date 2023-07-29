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
}

void App::Init()
{
	Log::Init();

	BA_LOG_INFO("Initializing {} App.", m_Name);
}

void App::Terminate()
{
	BA_LOG_INFO("Terminating {} App.", m_Name);
}
