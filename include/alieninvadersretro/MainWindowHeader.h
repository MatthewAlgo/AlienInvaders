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
#  include <fstream>
#  include <string>
#  include <thread>
#  include <sstream>

#  include "VirtualWindow.h"
#  include "ImguiRendererForWindow.h"
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

    // Imgui Context Pointer
    std::unique_ptr<ImGUIRenderer> ImGuiRenderer;
    // Variables related to the textures and design elements
  public:
    // Structure to retain information about the players on the leaderboard
    struct PlayerInfo {
      std::pair<std::string, int> PlayerNameAndScore;
    };
    std::vector<PlayerInfo> PlayerInfoList;
    std::vector<std::string> RawFileData;
    
    MainWindowClass(const std::string TITLE, int W, int H) : VirtualWindowClass(TITLE, W, H){ RawFileData = this->RawFileReader("Scores.txt"); }; // Loads the Scores from file when the window is opened - this->ScoresLoaderLocal("Scores.txt");
    ~MainWindowClass() = default;  // Auto deallocate smart pointers

    void MainWindowThreadExecution(
        TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& ITEM_HOLDER) override;
    void DrawInsideMainWindow(sf::RenderWindow* WINDOW, sf::Thread* WINTHREAD,
                              MainWindowClass* C);
    void RenderTextures(
        DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER) override;
    
    
    void ScoresLoaderLocal(std::string FileName); // A function to load the best scores from a file
    void ScoresSaverLocal(std::string FileName); // A function to save the best scores to a file
    int getBestScoreLocal(std::string FileName); // A function to get the best score from the file
    std::vector<std::string> RawFileReader(std::string FileName); // A function to get the scores from the file
  };
};  // namespace MatthewsNamespace

#  pragma endregion CLASS_REGION

#endif