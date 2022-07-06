#include "alieninvadersretro/ImguiRendererForWindow.h"

MatthewsNamespace::ImGUIRenderer::ImGUIRenderer(sf::RenderWindow* T) {
  // We define constructor functions here
  SFMLWindow = T;  // We create a new pointer
  ImGui::SFML::Init(*T);  // We initialize the window using the object pointed to
  DeltaClock.restart();
}

void MatthewsNamespace::ImGUIRenderer::ToBeCalledAfterEventHandling(sf::Event* Ev) {
  ImGui::SFML::ProcessEvent(*SFMLWindow, *Ev);
}
void MatthewsNamespace::ImGUIRenderer::RenderImguiContents(){
  ImGui::SFML::Render(*SFMLWindow);
}

void MatthewsNamespace::ImGUIRenderer::ToBeCalledForDrawingWindowElements() {
  // this->DeltaClock.restart(); // Restarts the delta clock upon drawing

  ImGui::SFML::Update(*SFMLWindow, this->DeltaClock.restart());
  ImGui::ShowDemoWindow();  // Shows a demo window for debugging purposes
  ImGui::Begin("Hello, world!");
  ImGui::Button("Look at this pretty button");
  ImGui::End();
}

// Getters
sf::Clock* MatthewsNamespace::ImGUIRenderer::getDeltaClock() {  // Clock
  return &DeltaClock;
}
sf::RenderWindow* MatthewsNamespace::ImGUIRenderer::getSFMLWindow() {  // SFMLWindow
  return SFMLWindow;
}

// Setters
void MatthewsNamespace::ImGUIRenderer::setDeltaClock(sf::Clock Delta) { DeltaClock = Delta; }
void MatthewsNamespace::ImGUIRenderer::setSFMLWindow(sf::RenderWindow* T) {
  SFMLWindow = T;
}
