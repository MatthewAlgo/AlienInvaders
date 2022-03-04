#pragma once
#ifndef P_STATS_WINDOW_H
#  define P_STATS_WINDOW_H

#  include <SFML/Graphics.hpp>
#  include <SFML/System.hpp>
#  include <SFML/Window.hpp>
#  include <functional>
#  include <iostream>
#  include <memory>
#  include <optional>

#  include "VirtualWindow.h"
namespace MatthewsNamespace {
  class PlayerStats : public virtual MatthewsNamespace::VirtualWindowClass {
  public:
    PlayerStats(const PlayerStats&) = delete;
    PlayerStats(const std::string Title, int W, int H) : VirtualWindowClass(Title, W, H) {}
    ~PlayerStats() = default;

    void MainWindowThreadExecution(
        TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& ITEM_HOLDER) override;
    void DrawInsideMainWindow(sf::RenderWindow* WINDOW, sf::Thread* WINTHREAD,
                              VirtualWindowClass* C) override;
    void RenderTextures(
        DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER) override;
  };
}  // namespace MatthewsNamespace

#endif