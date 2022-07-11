# pragma once

#  include <imgui-sfml/imgui-SFML.h>
#  include <imgui/imgui.h>

#  include <SFML/Graphics.hpp>
#  include <SFML/Window.hpp>
#  include <SFML/System.hpp>
#  include <iostream>
#  include <vector>
#  include <memory>


#  pragma region LibraryFuncs
namespace MatthewsNamespace {
  class ImGUIRenderer {
  protected:
    sf::RenderWindow* SFMLWindow;
    sf::Clock DeltaClock;
    
  public:
    // Constructors
    ImGUIRenderer(sf::RenderWindow* T);
    ~ImGUIRenderer(){ SFMLWindow = NULL; delete SFMLWindow; };

    // Library Functions
    void ToBeCalledAfterEventHandling(sf::Event* Ev);    
    void ToBeCalledForDrawingWindowElements(std::vector<std::string> VectorOfScores);
    void RenderImguiContents();

    // Getters
    sf::Clock* getDeltaClock(); // Clock
     
    sf::RenderWindow* getSFMLWindow(); // SFMLWindow

    // Setters
    void setDeltaClock(sf::Clock Delta);
    void setSFMLWindow(sf::RenderWindow* T);

  };
}  // namespace MatthewsNamespace

# pragma endregion LibraryFuncs