#include "alieninvadersretro/ImguiRendererForWindow.h"

MatthewsNamespace::ImGUIRenderer::ImGUIRenderer(sf::RenderWindow* T) {
  // We define constructor functions here
  SFMLWindow = std::make_shared<sf::RenderWindow>(T);         // The pointer now points to the window passed as parameter
  ImGui::SFML::Init(*T);  // We initialize the window using the object pointed to
  DeltaClock.restart();
}

void MatthewsNamespace::ImGUIRenderer::ToBeCalledAfterEventHandling(sf::Event* Ev) {
  ImGui::SFML::ProcessEvent(*SFMLWindow, *Ev);
}
void MatthewsNamespace::ImGUIRenderer::RenderImguiContents() { ImGui::SFML::Render(*SFMLWindow); }

void MatthewsNamespace::ImGUIRenderer::ToBeCalledForDrawingWindowElements(
    std::vector<std::string> VectorOfScores, std::string WindowName) {
  // this->DeltaClock.restart(); // Restarts the delta clock upon drawing

  ImGui::SFML::Update(*SFMLWindow, this->DeltaClock.restart());
  // ImGui::ShowDemoWindow();  // Shows a demo window for debugging purposes

  // Only if we render inside the main window of the game
  if (WindowName == "Main Window") {
    // Set a fixed size and position for the scores window
    ImGui::SetNextWindowPos(ImVec2(25, 50));
    ImGui::SetNextWindowSize(ImVec2(275, 200));

    ImGui::Begin("Leaderboard (Money Makers)");
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Winners at the game");
    ImGui::BeginChild("Scores", ImVec2(0, 0), true);
    for (int n = 0; n < VectorOfScores.size(); n++)
      ImGui::Text("%04d: %s", n, VectorOfScores[n].c_str());
    ImGui::EndChild();

    // That was the first window

    ImGui::End();
  }
}

void MatthewsNamespace::ImGUIRenderer::ToBeCalledForDrawingWindowElements(std::string WindowName) {
  ImGui::SFML::Update(*SFMLWindow, this->DeltaClock.restart());
  if (WindowName == "Animation Window") {
    ImGui::SetNextWindowPos(ImVec2(350, 25));
    ImGui::SetNextWindowSize(ImVec2(275, 50));

    ImGui::Begin("Please insert your name");
    ImGui::InputText("Name", getStringForInputText(), 255); // Set buffer size to 255
    // We need to render the imgui screen right after or while the apparition of the End Game screen
    ImGui::End();
  }
}

// Getters
sf::Clock* MatthewsNamespace::ImGUIRenderer::getDeltaClock() {  // Clock
  return &this->DeltaClock;
}
sf::RenderWindow* MatthewsNamespace::ImGUIRenderer::getSFMLWindow() {  // SFMLWindow
  return this->SFMLWindow.get();
}
char* MatthewsNamespace::ImGUIRenderer::getStringForInputText() {
  return this->StringForInputText;
}  // StringForInputText

// Setters
void MatthewsNamespace::ImGUIRenderer::setDeltaClock(sf::Clock Delta) { DeltaClock = Delta; }
void MatthewsNamespace::ImGUIRenderer::setSFMLWindow(sf::RenderWindow* T) { SFMLWindow = std::make_shared<sf::RenderWindow>(T); }
