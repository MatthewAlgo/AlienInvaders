#pragma once
#ifndef MAIN_WINDOW_HEADER_H
#  define MAIN_WINDOW_HEADER_H

#  pragma region INCLUDES
#  include <SFML/Audio.hpp>
#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <SFML/Window.hpp>
#  include <functional>
#  include <iostream>
#  include <string>
#  include <thread>

#  include "VirtualWindow.h"
#  pragma endregion INCLUDES

#  define U_P std::unique_ptr

#  pragma region CLASS_REGION
namespace MatthewsNamespace {
  class MainWindowClass : public virtual MatthewsNamespace::VirtualWindowClass {
  private:
    sf::Font GlobalWindowFont;
    sf::Text GreetingText, TextBTN1, TextBTN2;
    ImageToBeDrawn MenuBox1, MenuBox2, MenuBox3;
    std::unique_ptr<ImageToBeDrawn> WindowTitleTextbox;

    // Variables related to the textures and design elements
  public:
    MainWindowClass(const std::string TITLE, int W, int H) : VirtualWindowClass(TITLE, W, H){};
    ~MainWindowClass() = default;  // Auto deallocate smart pointers

    void MainWindowThreadExecution(
        TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& ITEM_HOLDER) override;
    void DrawInsideMainWindow(sf::RenderWindow* WINDOW, sf::Thread* WINTHREAD,
                              VirtualWindowClass* C) override;
    void RenderTextures(
        DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER) override;
  };
};  // namespace MatthewsNamespace

#  pragma endregion CLASS_REGION

#endif