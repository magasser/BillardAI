#include "bapch.h"
#include "UILayer.h"

#include <imgui.h>
#include <imgui-SFML.h>

#include "App.h"
#include "Settings.h"

void UILayer::OnAttach()
{
	ImGui::SFML::Init(App::GetWindow());
}

void UILayer::OnDetach()
{
	ImGui::SFML::Shutdown();
}

void UILayer::OnUpdate(float deltaTime)
{
	ImGui::SFML::Update(App::GetWindow(), sf::seconds(deltaTime));
}

void UILayer::OnUIRender()
{
	ImGui::Begin("Settings");
	ImGui::Checkbox("Show Hitboxes", &Settings::ShowHitboxes);
	ImGui::InputInt("Index", (int*)&Settings::Index);
	ImGui::SliderFloat2("Position", &Settings::Position.x, -0.0f, 260.0f, "%.1f");
	ImGui::SliderFloat2("Points 1", &Settings::Points[0].x, -100.0f, 100.0f, "%.1f");
	ImGui::SliderFloat2("Points 2", &Settings::Points[1].x, -100.0f, 100.0f, "%.1f");
	ImGui::SliderFloat2("Points 3", &Settings::Points[2].x, -100.0f, 100.0f, "%.1f");
	ImGui::SliderFloat2("Points 4", &Settings::Points[3].x, -100.0f, 100.0f, "%.1f");
	ImGui::SliderFloat2("Cue Ball Impulse", &Settings::CueBallImpuse.x, -3000.0f, 3000.0f, "%.1f");
	ImGui::End();

	ImGui::SFML::Render(App::GetWindow());
}

void UILayer::OnEvent(Event& event)
{
	ImGui::SFML::ProcessEvent(App::GetWindow(), event);
}
