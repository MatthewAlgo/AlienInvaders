#include "alieninvadersretro/ImguiRendererForWindow.h"

MatthewsNamespace::ImGUIRenderer::ImGUIRenderer(sf::RenderWindow* T) {
  // Init the memory for the text input
  StringForInputText = new char[256];

  // We define constructor functions here
  SFMLWindow = T;         // The pointer now points to the window passed as parameter
  ImGui::SFML::Init(*T);  // We initialize the window using the object pointed to
  DeltaClock.restart();

  // Imgui Rounded corners
  ImGui::GetStyle().WindowRounding = 10;  // <- Set this on init or use ImGui::PushStyleVar()
  ImGui::GetStyle().ChildRounding = 10;
  ImGui::GetStyle().FrameRounding = 10;
  ImGui::GetStyle().GrabRounding = 10;
  ImGui::GetStyle().PopupRounding = 10;
  ImGui::GetStyle().ScrollbarRounding = 10;

  ImGuiStyle* style = &ImGui::GetStyle();

  // Light style from Pacôme Danhiez (user itamago)
  // https://github.com/ocornut/imgui/pull/511#issuecomment-175719267
  style->Alpha = 1.0f;
  style->Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
  style->Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
  style->Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
  style->Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
  style->Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
  style->Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
  style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
  style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  style->Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
  style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
  style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
  style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
  style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
  style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
  style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
  style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
  style->Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
  style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style->Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
  style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
  style->Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
  style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style->Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
  style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  style->Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

  style = nullptr;
  delete style;
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
    // ImGui::InputText("Name", getStringForInputText(), 256);  // Set buffer size to 256
    // We need to render the imgui screen right after or while the apparition of the End Game screen
    ImGui::End();
  }
}

// Getters
sf::Clock* MatthewsNamespace::ImGUIRenderer::getDeltaClock() {  // Clock
  return &this->DeltaClock;
}
sf::RenderWindow* MatthewsNamespace::ImGUIRenderer::getSFMLWindow() {  // SFMLWindow
  return this->SFMLWindow;
}
char* MatthewsNamespace::ImGUIRenderer::getStringForInputText() {
  return this->StringForInputText;
}  // StringForInputText

// Setters
void MatthewsNamespace::ImGUIRenderer::setDeltaClock(sf::Clock Delta) { DeltaClock = Delta; }
void MatthewsNamespace::ImGUIRenderer::setSFMLWindow(sf::RenderWindow* T) { SFMLWindow = T; }
