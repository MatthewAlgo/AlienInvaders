#include "alieninvadersretro/AnimationWindow.h"  // Grabs all related includes

// INCLUDE IMGUI
#include "imgui-sfml/imgui-SFML.h"
#include "imgui/imgui.h"

#pragma region MAINCLASS_FUNC_IMPLEMENTATIONS
int MatthewsNamespace::EnemySpaceShipBullet::DAMAGE_SUPPLIER = 0;
int MatthewsNamespace::AnimationWindow::ANIMATION_INSTANCES = 0;

void MatthewsNamespace::AnimationWindow::MainWindowThreadExecution(
    TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& ITEM_HOLDER) {
  sf::WindowHandle handle
      = ITEM_HOLDER.getA()->getSystemHandle();  // Use the handle with OS specific functions

  // Main Window Settings
  ITEM_HOLDER.getA()->setActive(true);
  ITEM_HOLDER.getA()->setVerticalSyncEnabled(true);
  ITEM_HOLDER.getA()->setFramerateLimit(30);
  ANIMATION_INSTANCES = 1;

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
    MatthewsNamespace::BoomBox::RandomSongGenerator();
  }

  // Initialize the Imgui Renderer
  this->ImGuiRenderer = std::make_unique<ImGUIRenderer>(ITEM_HOLDER.getA());
  // ImGui::CreateContext();
  // ImGuiIO &io = ImGui::GetIO(); // Add imgui Hooks


  // Welcome effect by the boombox
  BoomBox::WelcomeEffect();

  // Display main Window
  while (ITEM_HOLDER.getA()->isOpen()) {
    sf::Event* Event = new sf::Event();

    ImGUIRenderer::IMGUI_Mutex.lock();
    
    while (ITEM_HOLDER.getA()->pollEvent(*Event)) {
      // Event Handling for imgui
      if(*SpaceShipMainPlayer.getLife() <= 0) // If the player is dead, we catch imgui events
        this->ImGuiRenderer->ToBeCalledAfterEventHandling(Event);

      if (Event->type == sf::Event::Closed) {
        try {
          // Delete players and their bullets
          for (int i{}; i < VectorOfEnemies.size(); ++i) {
            VectorOfEnemies.at(i)->Die();
            // EnemySpaceShip* Iterator = VectorOfEnemies.at(i).get();
            // delete Iterator;
            VectorOfEnemies.erase(VectorOfEnemies.begin() + i);
          }

          for (unsigned int i{}; i < SpaceShipMainPlayer.BulletDeque.size();
               i++) {  // Manage and free up the memory
            // SpaceShipBullet* it = SpaceShipMainPlayer.BulletDeque.at(i).get();
            // delete it;
            // it = nullptr;
            SpaceShipMainPlayer.BulletDeque.erase(SpaceShipMainPlayer.BulletDeque.begin() + i);
          }
          BoomBox::WindowSoundEffect();
          if (BoomBox::IS_MUSIC_ENABLED) {
            BoomBox::getMainTheme()->play();
          }
          // Stop the BoomBox for AnimationWindow
          if (BoomBox::LocalDJ->SOUND_MAIN.getStatus() == sf::SoundSource::Status::Playing) {
            BoomBox::LocalDJ->SOUND_MAIN.stop();
          }
          
          delete this->ParticleGenerator.get();  // Delete the random particles generator

          // Clean up memory occupied by the window
          ITEM_HOLDER.getA()->close();
          delete MainWindowVideo.get();
          ANIMATION_INSTANCES = 0;
          ImGUIRenderer::IMGUI_Mutex.unlock();
         
          ImGui::SFML::Shutdown(*ITEM_HOLDER.getA());
          // ImGui::DestroyContext();
          MainWindowThread->terminate();
          
        } catch (std::exception E) {
        }
        break;
      } else if (Event->type == sf::Event::MouseButtonReleased) {
      } else if (Event->type == sf::Event::KeyPressed) {
        if (Event->key.code == sf::Keyboard::Escape) {  // Exits on ESC pressed
          try {
            // Delete players and their bullets
            for (int i{}; i < VectorOfEnemies.size(); ++i) {
              VectorOfEnemies.at(i)->Die();
              // EnemySpaceShip* Iterator = VectorOfEnemies.at(i).get();
              // delete Iterator;
              VectorOfEnemies.erase(VectorOfEnemies.begin() + i);
            }

            for (unsigned int i{}; i < SpaceShipMainPlayer.BulletDeque.size();
                 i++) {  // Manage and free up the memory
              // SpaceShipBullet* it = SpaceShipMainPlayer.BulletDeque.at(i).get();
              // delete it;
              // it = nullptr;
              SpaceShipMainPlayer.BulletDeque.erase(SpaceShipMainPlayer.BulletDeque.begin() + i);
            }
            BoomBox::WindowSoundEffect();  // Start the BoomBox for MainWindow
            if (BoomBox::IS_MUSIC_ENABLED == 1) {
              // BoomBox::StartMainThemeSong();
              BoomBox::getMainTheme()->play();
            }
            // Stop the BoomBox for AnimationWindow
            if (BoomBox::LocalDJ->SOUND_MAIN.getStatus() == sf::SoundSource::Status::Playing) {
              BoomBox::LocalDJ->SOUND_MAIN.stop();
            }
            
            delete this->ParticleGenerator.get();  // Delete the random particles generator

            // Clean up memory occupied by the window
            ITEM_HOLDER.getA()->close();
            delete MainWindowVideo.get();
            ANIMATION_INSTANCES = 0;
            ImGUIRenderer::IMGUI_Mutex.unlock();
            
            ImGui::SFML::Shutdown(*ITEM_HOLDER.getA());
            // ImGui::DestroyContext();
            MainWindowThread->terminate();
            
          } catch (std::exception E) {
          }
          break;
        }
        if (Event->key.code == sf::Keyboard::Enter) {
          if (*SpaceShipMainPlayer.getLife() <= 0) {  // Active only if the player is dead
            // We get the text currently entered in the ImGui instance and append it to the file      
            ImGuiRenderer->getStringForInputText();


            // We open the text file and append the text
            std::ofstream fout("Scores.txt", std::ios_base::app);
            fout << ImGuiRenderer->getStringForInputText() << " --- " << Player1Score << std::endl;
            fout.close(); // We close the file
            
            // We add the score to the vector of scores
            MainWindowClass::PlayerInfo playerinfo; 
            {
              playerinfo.PlayerNameAndScore.first = ImGuiRenderer->getStringForInputText();
              playerinfo.PlayerNameAndScore.second = Player1Score;
            }
            MainWindowClass::PlayerInfoList.push_back(playerinfo);

            MainWindowClass::sortScoresVector(MainWindowClass::PlayerInfoList); // We sort the scores vector  
            MainWindowClass::scoresSaverLocal("Scores.txt"); // Then we save the scores to the file

            MatthewsNamespace::MainWindowClass::RawFileData
                = MatthewsNamespace::MainWindowClass::RawFileReader("Scores.txt");
            MatthewsNamespace::MainWindowClass::ScoresLoaderLocal("Scores.txt");
            
            // We close the window immediately to prevent other interactions
            try {
              // Delete players and their bullets
              for (int i{}; i < VectorOfEnemies.size(); ++i) {
                VectorOfEnemies.at(i)->Die();
                VectorOfEnemies.erase(VectorOfEnemies.begin() + i);
              }

              for (unsigned int i{}; i < SpaceShipMainPlayer.BulletDeque.size();
                   i++) {  // Manage and free up the memory
                // SpaceShipBullet* it = SpaceShipMainPlayer.BulletDeque.at(i).get();
                // delete it;
                // it = nullptr;
                SpaceShipMainPlayer.BulletDeque.erase(SpaceShipMainPlayer.BulletDeque.begin() + i);
              }
              BoomBox::WindowSoundEffect();  // Start the BoomBox for MainWindow
              if (BoomBox::IS_MUSIC_ENABLED) {
                // BoomBox::StartMainThemeSong();
                BoomBox::getMainTheme()->play();
              }
              // Stop the BoomBox for AnimationWindow
              if (BoomBox::LocalDJ->SOUND_MAIN.getStatus() == sf::SoundSource::Status::Playing) {
                BoomBox::LocalDJ->SOUND_MAIN.stop();
              }
              
              delete this->ParticleGenerator.get();  // Delete the random particles generator

              // Clean up memory occupied by the window
              ITEM_HOLDER.getA()->close();
              delete MainWindowVideo.get();
              ANIMATION_INSTANCES = 0;
              ImGUIRenderer::IMGUI_Mutex.unlock(); 
               
              ImGui::SFML::Shutdown(*ITEM_HOLDER.getA()); 
              // ImGui::DestroyContext();
              MainWindowThread->terminate();
              
            } catch (std::exception E) {
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
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            SpaceShipMainPlayer.MoveLeft();
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            SpaceShipMainPlayer.MoveRight();
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            SpaceShipMainPlayer.MoveUp();
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            SpaceShipMainPlayer.MoveDown();
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            SpaceShipMainPlayer.Shoot(Player1Score);
          }
        }
        ImGUIRenderer::IMGUI_Mutex.unlock();
      } catch (std::exception E) {
        std::cout << "Exception caught: " << E.what() << std::endl;
      }
    }

    // Check For BoomBox Status
    if (!(BoomBox::LocalDJ->SOUND_MAIN.getStatus() == sf::SoundSource::Status::Playing)) {
      MatthewsNamespace::BoomBox::RandomSongGenerator();
    }

    std::free(Event);
    // ImGUIRenderer::IMGUI_Mutex.lock();  // We lock the mutex for Imgui
    AnimationWindow* MyWindowVirt
        = dynamic_cast<AnimationWindow*>(ITEM_HOLDER.getC());  // Polymorphic conversion
    MatthewsNamespace::AnimationWindow::DrawInsideMainWindow(ITEM_HOLDER.getA(), ITEM_HOLDER.getB(),
                                                             MyWindowVirt);
    MyWindowVirt = NULL;
    delete MyWindowVirt;
    // ImGUIRenderer::IMGUI_Mutex.unlock();  // We unlock the mutex to allow the rendering of the other window
  }
}
void MatthewsNamespace::AnimationWindow::DrawInsideMainWindow(
    sf::RenderWindow* WINDOW, sf::Thread* WINTHREAD, MatthewsNamespace::AnimationWindow* C) {
  if (PausedParity % 2 == 0) {
    if (*SpaceShipMainPlayer.getLife() > 0) {  // The player has lives and the game is running
      enemy_spawn_clock++;

      WINDOW->clear(sf::Color::Red);
      WINDOW->draw(BackGround->SPRITE);

      // Draw the current player score
      ScoreText.setString("Player Score: " + std::to_string(Player1Score));
      LivesText.setString("Lives Remaining: " + std::to_string(*SpaceShipMainPlayer.getLife()));
      WINDOW->draw(ScoreText);
      WINDOW->draw(LivesText);

      WINDOW->draw(*SpaceShipMainPlayer.getSpaceShipSprite());  // Draw the first spaceship
      // Manage the bullets for the first spaceship
      Player1Score += SpaceShipMainPlayer.IterateThroughBullets(WINDOW, VectorOfEnemies);
      SpaceShipMainPlayer.FreeUpMemoryBullets();

      // For the enemies
      if (enemy_spawn_clock % 100 == 0) {
        // Spawn an enemy
        std::unique_ptr<EnemySpaceShip> Espace = std::make_unique<EnemySpaceShip>();
        VectorOfEnemies.push_back(std::move(Espace));
        VectorOfEnemies.back()->setMainWindowSize(WINDOW->getSize().x, WINDOW->getSize().y);
        VectorOfEnemies.back()->GenerateInDrawFunctionOfMainWindow(WINDOW, "EnemySpaceShip.png");
        enemy_spawn_clock = MatthewsNamespace::RandomParticlesGenerator::Mersenne_Twister_Generator(
            60 + LevelUpConstant, 70 + LevelUpConstant);
      }
      for (int i{}; i < VectorOfEnemies.size(); ++i) {
        VectorOfEnemies.at(i)->Draw_IterateExistingItem(WINDOW);
        VectorOfEnemies.at(i)->Shoot();
        VectorOfEnemies.at(i)->DrawBulletsInWindow(
            WINDOW, SpaceShipMainPlayer.getSpaceShipPosition().x,
            SpaceShipMainPlayer.getSpaceShipPosition().y, SpaceShipMainPlayer.Life);
        VectorOfEnemies.at(i)->FreeUpMemoryFromBullets(WINDOW);

        // If offsetted -> Delete the enemy and subtract 1 life
        if (VectorOfEnemies.at(i)->getSpaceShipPosition().y > WINDOW->getSize().y + 20) {
          (*SpaceShipMainPlayer.getLife())--;
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
            EnemySpaceShip::LIFE_SUPPLIER++;
            BoomBox::EvilEffect();
          }
          if (LevelUpConstant + 5 <= 25)  // 5 Difficulty Levels
            LevelUpConstant += 5;
          else if (Player1Score % 20'000)
            EnemySpaceShipBullet::DAMAGE_SUPPLIER++;
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
      LivesText.setString("Lives Remaining: " + std::to_string(*SpaceShipMainPlayer.getLife()));
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
    LivesText.setString("Lives Remaining: " + std::to_string(*SpaceShipMainPlayer.getLife()));
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
void MatthewsNamespace::AnimationWindow::RenderTextures(
    DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER) {
  // Inside a separate thread -> Background
  BackGround = std::make_unique<ImageToBeDrawn>();
  BackGround->TEXTURE.loadFromFile("SpaceWallpaper.jpg");
  BackGround->SPRITE.setTexture(BackGround->TEXTURE);
  BackGround->SPRITE.setScale(0.4, 0.4);

  // SpaceShip
  SpaceShipMainPlayer.getSpaceShipTexture()->loadFromFile("SpaceshipNo1.png");
  SpaceShipMainPlayer.setSpaceShipPosition(WWidth / 2, WHeight / 2);
  SpaceShipMainPlayer.getSpaceShipSprite()->setTexture(*SpaceShipMainPlayer.getSpaceShipTexture());
  SpaceShipMainPlayer.getSpaceShipSprite()->setScale(0.2, 0.2);

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

#pragma endregion MAINCLASS_FUNC_IMPLEMENTATIONS
