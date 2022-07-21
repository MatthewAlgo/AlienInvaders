#pragma once

#include <imgui-sfml/imgui-SFML.h>
#include <imgui/imgui.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <string>
#include <vector>

#pragma region LibraryFuncs
namespace MatthewsNamespace {
  class ImGUIRenderer {
  protected:
    sf::RenderWindow* SFMLWindow;
    sf::Clock DeltaClock;
    char* StringForInputText;  // = new char[256]

  public:
    // Constructors
    ImGUIRenderer(sf::RenderWindow* T);
    ~ImGUIRenderer() = default;

    // Library Functions
    void ToBeCalledAfterEventHandling(sf::Event* Ev);
    // Usually called for the main window
    void ToBeCalledForDrawingWindowElements(std::vector<std::string> VectorOfScores,
                                            std::string WindowName);

    // Called for other windows
    void ToBeCalledForDrawingWindowElements(std::string WindowName);

    void RenderImguiContents();

    // Getters
    sf::Clock* getDeltaClock();         // Clock
    sf::RenderWindow* getSFMLWindow();  // SFMLWindow
    char* getStringForInputText();      // StringForInputText

    // Setters
    void setDeltaClock(sf::Clock Delta);
    void setSFMLWindow(sf::RenderWindow* T);
  };
}  // namespace MatthewsNamespace

#pragma endregion LibraryFuncs