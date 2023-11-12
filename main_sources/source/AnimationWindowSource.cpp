#include "alieninvadersretro/AnimationWindow.h"  // Grabs all related includes

// INCLUDE IMGUI
#include "imgui-sfml/imgui-SFML.h"
#include "imgui/imgui.h"

#pragma region MAINCLASS_FUNC_IMPLEMENTATIONS

namespace GameNamespace {
  void AnimationWindow::freeUpMemorySpaceFromPlayerBulletsAfterWindowKill() {
    // Delete all the bullets of all players
    for (const auto& SpaceShipPlayer : SpaceShipPlayersVector) {
      for (unsigned int i{}; i < SpaceShipPlayer->BulletDeque.size();
           i++) {  // Manage and free up the memory
        SpaceShipPlayer->BulletDeque.erase(SpaceShipPlayer->BulletDeque.begin() + i);
      }
    }
  }

  bool AnimationWindow::thereAreStillPlayersInsideTheMatch() {
    // If there are still players inside the match, then continue to render the window
    bool there_are_still_players_inside_the_match = false;
    for (const auto& SpaceShipPlayer : SpaceShipPlayersVector) {
           if (SpaceShipPlayer->getLife() > 0) {
                    there_are_still_players_inside_the_match = true;
      }
    }
    return there_are_still_players_inside_the_match;

  }

  void AnimationWindow::comeBackToTheMainWindowFromGameWindow(
      TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& TripleItHolder) {
    BoomBox::WindowSoundEffect();  // Start the BoomBox for MainWindow
    if (BoomBox::IS_MUSIC_ENABLED == 1) {
      BoomBox::getMainTheme()->play();
    }
    // Stop the BoomBox for AnimationWindow
    if (BoomBox::LocalDJ->SOUND_MAIN.getStatus() == sf::SoundSource::Status::Playing) {
      BoomBox::LocalDJ->SOUND_MAIN.stop();
    }

    delete this->ParticleGenerator.get();  // Delete the random particles generator

    // Clean up memory occupied by the window
    TripleItHolder.getA()->close();
    delete MainWindowVideo.get();
    AnimationWindow::DeleteInstance();
    ImGUIRenderer::IMGUI_Mutex.unlock();

    ImGui::SFML::Shutdown(*TripleItHolder.getA());
    MainWindowThread->terminate();
  }

  void AnimationWindow::MainWindowThreadExecution(
      TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& TripleItHolder) {
    sf::WindowHandle handle
        = TripleItHolder.getA()->getSystemHandle();  // Use the handle with OS specific functions

    // Main Window Settings
    TripleItHolder.getA()->setActive(true);
    TripleItHolder.getA()->setVerticalSyncEnabled(true);
    TripleItHolder.getA()->setFramerateLimit(30);

    //////// Create a separate thread to render the textures
    if (!((BoomBox::getMainTheme()->getStatus() == sf::SoundSource::Status::Paused)
          || (BoomBox::getMainTheme()->getStatus() == sf::SoundSource::Status::Stopped))) {
      BoomBox::getMainTheme()->pause();
    }
    std::unique_ptr<sf::Thread> ThreadRenderer
        = std::make_unique<sf::Thread>([&]() -> void {});  // TODO: Render Textures Asynchronously
    std::unique_ptr<DoubleItemHolder<sf::RenderWindow, VirtualWindowClass>> CurrentHolder
        = std::make_unique<DoubleItemHolder<sf::RenderWindow, VirtualWindowClass>>(
            WindowPointer.get(), this);
    RenderTextures(*CurrentHolder.get());

    // Basically generates a random song each time it is not playing
    if (!(BoomBox::LocalDJ->SOUND_MAIN.getStatus() == sf::SoundSource::Status::Playing)) {
      GameNamespace::BoomBox::RandomSongGenerator();
    }

    // Initialize the Imgui Renderer
    this->ImGuiRenderer = std::make_unique<ImGUIRenderer>(TripleItHolder.getA());

    // Welcome effect by the boombox
    BoomBox::WelcomeEffect();

    // Display main Window
    while (TripleItHolder.getA()->isOpen()) {
      auto* Event = new sf::Event();

      ImGUIRenderer::IMGUI_Mutex.lock();

      while (TripleItHolder.getA()->pollEvent(*Event)) {
        // Event Handling for imgui
        // We need to know if all the players are dead. If so, launch the off window. Create all the needed events by the imgui
        bool all_players_are_dead = true;
        for (const auto& SpaceShipNormalPlayer : SpaceShipPlayersVector) { // Getting an auto reference to the element
          if (SpaceShipNormalPlayer->getLife()
              > 0)  // If all the players are dead, we catch imgui events
            all_players_are_dead = false;
        }
        if (all_players_are_dead)
            this->ImGuiRenderer->ToBeCalledAfterEventHandling(Event);

        
        
        if (Event->type == sf::Event::Closed) {
          try {
            // Delete players and their bullets
            for (int i{}; i < VectorOfEnemies.size(); ++i) {
              VectorOfEnemies.at(i)->Die();
              VectorOfEnemies.erase(VectorOfEnemies.begin() + i);
            }

            // Deletes all the bullets of the players that are in the game
            this->freeUpMemorySpaceFromPlayerBulletsAfterWindowKill();

            // Come back to the main window
            this->comeBackToTheMainWindowFromGameWindow(TripleItHolder);

          } catch (std::exception E) {
            std::cout << "Error occured while freeing up memory after quit: " << E.what() << "\n";
          }
          break;
        } else if (Event->type == sf::Event::MouseButtonReleased) {
            // If the mouse button has been released, handle this event -> nothing for now
        } else if (Event->type == sf::Event::KeyPressed) {
          if (Event->key.code == sf::Keyboard::Escape) {  // Exits on ESC pressed
            try {
              // Delete players and their bullets
              for (int i{}; i < VectorOfEnemies.size(); ++i) {
                VectorOfEnemies.at(i)->Die();
                VectorOfEnemies.erase(VectorOfEnemies.begin() + i);
              }

              // Deletes all the bullets of the players that are in the game
              this->freeUpMemorySpaceFromPlayerBulletsAfterWindowKill();

              // Come back to the main window after killing the animation window
              this->comeBackToTheMainWindowFromGameWindow(TripleItHolder);

            } catch (std::exception E) {
            }
            break;
          }
          if (Event->key.code == sf::Keyboard::Enter) {
              // If all the players are dead, we het the socker of each player
            bool all_players_are_dead = true;
            for (const auto& SpaceShipPlayer : SpaceShipPlayersVector) {
              if (SpaceShipPlayer->getLife() > 0) {
                all_players_are_dead = false;
              }
            }
            if (all_players_are_dead) {  // Active only if the player is dead
              // We get the text currently entered in the ImGui instance and append it to the file
              ImGuiRenderer->getStringForInputText();

              // We open the text file and append the text
              std::ofstream fout("Scores.txt", std::ios_base::app);

              // For each player, add its score to the board of scores
              fout << ImGuiRenderer->getStringForInputText() << " --- " << Player1Score
                   << std::endl;

              fout.close();  // We close the file

              // We add the score to the vector of scores
              MainWindowClass::PlayerInfo playerinfo;
              {
                playerinfo.PlayerNameAndScore.first = ImGuiRenderer->getStringForInputText();
                playerinfo.PlayerNameAndScore.second = Player1Score;
              }
              MainWindowClass::PlayerInfoList.push_back(playerinfo);

              MainWindowClass::sortScoresVector(
                  MainWindowClass::PlayerInfoList);  // We sort the scores vector
              MainWindowClass::scoresSaverLocal(
                  "Scores.txt");  // Then we save the scores to the file

              GameNamespace::MainWindowClass::RawFileData
                  = GameNamespace::MainWindowClass::RawFileReader("Scores.txt");
              GameNamespace::MainWindowClass::ScoresLoaderLocal("Scores.txt");

              // We close the window immediately to prevent other interactions
              try {
                // Delete players and their bullets
                for (int i{}; i < VectorOfEnemies.size(); ++i) {
                  VectorOfEnemies.at(i)->Die();
                  VectorOfEnemies.erase(VectorOfEnemies.begin() + i);
                }

                // Free up the memory from the player bullets
                freeUpMemorySpaceFromPlayerBulletsAfterWindowKill();

                // Return to the music and theme of the main game window
                comeBackToTheMainWindowFromGameWindow(TripleItHolder);

              } catch (std::exception E) {
                std::cout << "Exception caught while freeing up the memory and coming back from "
                             "the AnimationWindow\n";
              }
              break;
            }
            // This is where window closing process ends
          }
          if (Event->key.code == sf::Keyboard::P) {  // && SpaceShipMainPlayer.getLife() > 0
            PausedParity++;
            BoomBox::WindowSoundEffect();
          }

        } else if (Event->type == sf::Event::TextEntered) {
        }
      }
      // if(!(Player1Score % 10'000 == 0 && Player1Score != 0)) // Game over screen
      //   ImGUIRenderer::IMGUI_Mutex.unlock();  // We lock the mutex for Imgui
      ImGUIRenderer::IMGUI_Mutex.unlock();

      // Check for continuous key presses - if the game is not paused
      if (PausedParity % 2 == 0) {
        try {
          ImGUIRenderer::IMGUI_Mutex.lock();
          if (!ImGui::GetIO().WantCaptureKeyboard) {
            // For each player, check its control type
          }
          ImGUIRenderer::IMGUI_Mutex.unlock();
        } catch (std::exception E) {
          std::cout << "Exception caught: " << E.what() << std::endl;
        }
      }

      // Check For BoomBox Status
      if (!(BoomBox::LocalDJ->SOUND_MAIN.getStatus() == sf::SoundSource::Status::Playing)) {
        GameNamespace::BoomBox::RandomSongGenerator();
      }

      delete Event;
      AnimationWindow* MyWindowVirt
          = dynamic_cast<AnimationWindow*>(TripleItHolder.getC());  // Polymorphic conversion
      GameNamespace::AnimationWindow::DrawInsideMainWindow(TripleItHolder.getA(), TripleItHolder.getB(),
                                                           MyWindowVirt);
      MyWindowVirt = NULL;
      delete MyWindowVirt;
      // other window
    }
  }

  AnimationWindow* AnimationWindow::GetInstance(const std::string Title, int W, int H) {
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */

    if (AnimWin_ == nullptr) {
      AnimWin_ = new AnimationWindow(Title, W, H);
    }
    return AnimWin_;
  }

  void AnimationWindow::DeleteInstance() {
    delete AnimWin_;
    AnimWin_ = nullptr;
  }

  bool AnimationWindow::HasInstance() { 
      return AnimWin_ == nullptr;
  }

  void GameNamespace::AnimationWindow::DrawInsideMainWindow(sf::RenderWindow* WINDOW,
                                                            sf::Thread* WINTHREAD, GameNamespace::AnimationWindow* C) {

    // If the game is not paused, draw the players and the bullets and everything related to the general gameplay
    if (PausedParity % 2 == 0) {
      // If there are still players inside the match, then continue to render the window  
      if (SpaceShipMainPlayer->getLife() > 0) {  // The player has lives and the game is running
        enemy_spawn_clock++;

        WINDOW->clear(sf::Color::Red);
        WINDOW->draw(BackGround->SPRITE);

        // Draw the current player score
        ScoreText.setString("Player Score: " + std::to_string(Player1Score));
        LivesText.setString("Lives Remaining: " + std::to_string(SpaceShipMainPlayer->getLife()));
        WINDOW->draw(ScoreText);
        WINDOW->draw(LivesText);

        WINDOW->draw(*SpaceShipMainPlayer->getSprite());  // Draw the first spaceship
        // Manage the bullets for the first spaceship
        Player1Score += SpaceShipMainPlayer->IterateThroughBullets(WINDOW, VectorOfEnemies);
        SpaceShipMainPlayer->FreeUpMemoryBullets();

        // For the enemies
        if (enemy_spawn_clock % 100 == 0) {
          // Spawn an enemy
          std::unique_ptr<EnemySpaceShip> Espace = std::make_unique<EnemySpaceShip>();
          VectorOfEnemies.push_back(std::move(Espace));
          VectorOfEnemies.back()->setMainWindowSize(WINDOW->getSize().x, WINDOW->getSize().y);
          VectorOfEnemies.back()->GenerateInDrawFunctionOfMainWindow(WINDOW, "EnemySpaceShip.png");
          enemy_spawn_clock = GameNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(
              60 + LevelUpConstant, 70 + LevelUpConstant);
        }
        for (int i{}; i < VectorOfEnemies.size(); ++i) {
          VectorOfEnemies.at(i)->Draw_IterateExistingItem(WINDOW);
          VectorOfEnemies.at(i)->Shoot();
          VectorOfEnemies.at(i)->DrawBulletsInWindow(WINDOW, SpaceShipMainPlayer->getPosition().x,
                                                     SpaceShipMainPlayer->getPosition().y,
                                                     SpaceShipMainPlayer->getLife(), SpaceShip* spaceShip);
          VectorOfEnemies.at(i)->FreeUpMemoryFromBullets(WINDOW);

          // If offsetted -> Delete the enemy and subtract 1 life
          if (VectorOfEnemies.at(i)->getPosition().y > WINDOW->getSize().y + 20) {
            SpaceShipMainPlayer->setLife(SpaceShipMainPlayer->getLife() - 1);
            VectorOfEnemies.at(i)->Die();
            // EnemySpaceShip* Iterator = VectorOfEnemies.at(i).get();
            // delete Iterator;
            VectorOfEnemies.erase(VectorOfEnemies.begin() + i);
          }
        }

        // For the particle generator
        ParticleGenerator->Generate();
        ParticleGenerator->InLoopForParticles(WINDOW);
        ParticleGenerator->ClearMemory(WINDOW);

        // If the score % 10000 == 0 - increase the difficulty - enemies have more life
        if (Player1Score % 10'000 == 0 && Player1Score != 0) {
          Cnt1000++;
          if (Cnt1000 == 1) {
            // Do stuff to be executed once
            if (Player1Score == 50'000) {
              BoomBox::UpgradeEffect();  // Switch to double cannon configuration
            }
            if (Player1Score == 100'000) {
              BoomBox::UpgradeEffect();  // Switch to triple cannon configuration
            }
            if ((Player1Score > 100'000) && (Player1Score % 20'000 == 0)) {
              EnemySpaceShip::LIFE_SUPPLIER++;  // Increases the life of all enemies with 1
              BoomBox::EvilEffect();
            }
            if (LevelUpConstant + 5 <= 25)  // 5 Difficulty Levels
              LevelUpConstant += 5;
            else if (Player1Score % 20'000)
              EnemySpaceShipBullet::DAMAGE_SUPPLIER++;  // Increases the damage of all enemies with
                                                        // 1
          } else {
            Cnt1000 = 2;
          }
        } else {
          Cnt1000 = 0;
        }
      } else {  // Show game over screen -> Everything in here is rendered after the game is over
        WINDOW->clear(sf::Color::Red);
        WINDOW->draw(BackGround->SPRITE);

        // Draw the current player score
        ScoreText.setString("Player Score: " + std::to_string(Player1Score));
        LivesText.setString("Lives Remaining: " + std::to_string(SpaceShipMainPlayer->getLife()));
        WINDOW->draw(ScoreText);
        WINDOW->draw(LivesText);

        // For the particle generator
        ParticleGenerator->Generate();
        ParticleGenerator->InLoopForParticles(WINDOW);
        ParticleGenerator->ClearMemory(WINDOW);

        GameOverText.setString("Game Over");
        WINDOW->draw(GameOverText);
        PresskeyText.setString("Press ESC Key To Continue");
        WINDOW->draw(PresskeyText);
        // Draw the rectangle prompt with the name of the player

        ImGUIRenderer::IMGUI_Mutex.lock();

        this->ImGuiRenderer->ToBeCalledForDrawingWindowElements("Animation Window");
        this->ImGuiRenderer->RenderImguiContents();

        ImGUIRenderer::IMGUI_Mutex.unlock();

        EnemySpaceShipBullet::DAMAGE_SUPPLIER = 0;  // Reset the enemy damage supplier
        EnemySpaceShip::LIFE_SUPPLIER = 0;          // Reset the enemy life supplier
      }
    } else {  // The game is paused
      WINDOW->clear(sf::Color::Red);
      WINDOW->draw(BackGround->SPRITE);

      // Draw the current player score
      ScoreText.setString("Player Score: " + std::to_string(Player1Score));
      LivesText.setString("Lives Remaining: " + std::to_string(SpaceShipMainPlayer->getLife()));
      WINDOW->draw(ScoreText);
      WINDOW->draw(LivesText);

      // For the particle generator
      ParticleGenerator->Generate();
      ParticleGenerator->InLoopForParticles(WINDOW);
      ParticleGenerator->ClearMemory(WINDOW);

      GameOverText.setPosition(WWidth / 3.25, WHeight / 2 - 50);
      GameOverText.setString("Paused");
      WINDOW->draw(GameOverText);
      PresskeyText.setString("Press P Key To Continue");
      WINDOW->draw(PresskeyText);
      GameOverText.setPosition(
          WWidth / 4, WHeight / 2 - 50);  // Prepare the entity again to be used as a game over text
    }
    WINDOW->display();
  }
  void GameNamespace::AnimationWindow::RenderTextures(
      DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER) {
    // Inside a separate thread -> Background
    BackGround = std::make_unique<ImageToBeDrawn>();
    BackGround->TEXTURE.loadFromFile("SpaceWallpaper.jpg");
    BackGround->SPRITE.setTexture(BackGround->TEXTURE);
    BackGround->SPRITE.setScale(0.4, 0.4);

    // SpaceShip
    SpaceShipMainPlayer->getTexture()->loadFromFile("SpaceshipNo1.png");
    SpaceShipMainPlayer->setPosition(WWidth / 2, WHeight / 2);
    SpaceShipMainPlayer->getSprite()->setTexture(*SpaceShipMainPlayer->getTexture());
    SpaceShipMainPlayer->getSprite()->setScale(0.2, 0.2);

    // Render Font for text
    GlobalWindowFont.loadFromFile("Fonts/Emulogic.ttf");
    ScoreText.setFont(GlobalWindowFont);
    ScoreText.setCharacterSize(24);
    ScoreText.setFillColor(sf::Color::Yellow);
    ScoreText.setStyle(sf::Text::Bold);
    ScoreText.setPosition(WWidth / 100, WHeight / 100.0);

    LivesText.setFont(GlobalWindowFont);
    LivesText.setCharacterSize(24);
    LivesText.setFillColor(sf::Color::Red);
    LivesText.setStyle(sf::Text::Bold);
    LivesText.setPosition(WWidth / 100, WHeight / 15);

    GameOverText.setFont(GlobalWindowFont);
    GameOverText.setCharacterSize(50);
    GameOverText.setFillColor(sf::Color::Yellow);
    GameOverText.setStyle(sf::Text::Bold);
    GameOverText.setPosition(WWidth / 4, WHeight / 2 - 50);

    PresskeyText.setFont(GlobalWindowFont);
    PresskeyText.setCharacterSize(15);
    PresskeyText.setFillColor(sf::Color::Yellow);
    PresskeyText.setStyle(sf::Text::Bold);
    PresskeyText.setPosition(WWidth / 4 + 30, WHeight / 2);

    LevelUpText.setFont(GlobalWindowFont);
    LevelUpText.setCharacterSize(50);
    LevelUpText.setFillColor(sf::Color::Yellow);
    LevelUpText.setStyle(sf::Text::Bold);
    LevelUpText.setPosition(WWidth / 4 + 20, WHeight / 2);
  }

}  // namespace GameNamespace
#pragma endregion MAINCLASS_FUNC_IMPLEMENTATIONS
