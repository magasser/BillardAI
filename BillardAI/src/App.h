#pragma once

class App
{
public:
	App(const std::string& name);
	virtual ~App();

	void Run();

private:
	void Init();
	void Terminate();

private:
	std::string m_Name;
};
