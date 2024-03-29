#include "alieninvadersretro/BoomBox.h"

// Static variable compilation
bool MatthewsNamespace::BoomBox::IS_SOUND_ENABLED = 1;
bool MatthewsNamespace::BoomBox::IS_MUSIC_ENABLED = 1;
int MatthewsNamespace::BoomBox::BOOMBOX_INSTANCES = 0;

namespace MatthewsNamespace {
  std::unique_ptr<MatthewsNamespace::BoomBox::DJ> MatthewsNamespace::BoomBox::LocalDJ
      = std::make_unique<DJ>();
  std::vector<std::string> MatthewsNamespace::BoomBox::WavFilesFromDirectory;

  void MatthewsNamespace::BoomBox::MainWindowThreadExecution(
      TripleItemHolder<sf::RenderWindow, sf::Thread, VirtualWindowClass>& ITEM_HOLDER) {
    sf::WindowHandle handle
        = ITEM_HOLDER.getA()->getSystemHandle();  // Use the handle with OS specific functions
    // Main Window Settings
    ITEM_HOLDER.getA()->setActive(true);
    ITEM_HOLDER.getA()->setVerticalSyncEnabled(true);
    ITEM_HOLDER.getA()->setFramerateLimit(60);

    BOOMBOX_INSTANCES = 1;  // Trying to mimic a singleton pattern for now

    std::unique_ptr<DoubleItemHolder<sf::RenderWindow, VirtualWindowClass>> CurrentHolder
        = std::make_unique<DoubleItemHolder<sf::RenderWindow, VirtualWindowClass>>(WindowPointer.get(),
                                                                                   this);
    RenderTextures(*CurrentHolder.get());
    //////// Temporary - work in progress

    // Display main Window
    while (ITEM_HOLDER.getA()->isOpen()) {
      sf::Event* Event = new sf::Event();
      while (ITEM_HOLDER.getA()->pollEvent(*Event)) {
        if (Event->type == sf::Event::Closed) {
          ITEM_HOLDER.getA()->close();
          BoomBox::WindowSoundEffect();
          BOOMBOX_INSTANCES = 0;
          break;
        } else if (Event->type == sf::Event::MouseButtonReleased) {
          std::unique_ptr<sf::Mouse> MyMouse = std::make_unique<sf::Mouse>();

          if (MyMouse.get()->getPosition(*WindowPointer).x >= 100
              && MyMouse.get()->getPosition(*WindowPointer).x <= 400)
            if (MyMouse.get()->getPosition(*WindowPointer).y >= 350
                && MyMouse.get()->getPosition(*WindowPointer).y <= 450) {
              // Bottom button
              if (MatthewsNamespace::BoomBox::IS_SOUND_ENABLED) {
                MatthewsNamespace::BoomBox::IS_SOUND_ENABLED = false;
              } else {
                MatthewsNamespace::BoomBox::IS_SOUND_ENABLED = 1;
              }
            }
          if (MyMouse.get()->getPosition(*WindowPointer).x >= 100
              && MyMouse.get()->getPosition(*WindowPointer).x <= 400)
            if (MyMouse.get()->getPosition(*WindowPointer).y >= 20
                && MyMouse.get()->getPosition(*WindowPointer).y <= 120) {
              // Upper button
              if (MatthewsNamespace::BoomBox::IS_MUSIC_ENABLED) {
                MatthewsNamespace::BoomBox::IS_MUSIC_ENABLED = false;
                // Stop the BoomBox for AnimationWinow
                if (BoomBox::LocalDJ->SOUND_MAIN.getStatus() == sf::SoundSource::Status::Playing) {
                  BoomBox::LocalDJ->SOUND_MAIN.stop();
                  BoomBox::LocalDJ->SOUND_MAIN.resetBuffer();
                }
                // Stop the Main Window sound
                if (BoomBox::LocalDJ->MainThemeSound.getStatus()
                    == sf::SoundSource::Status::Playing) {
                  BoomBox::LocalDJ->MainThemeSound.stop();
                  BoomBox::LocalDJ->MainThemeSound.resetBuffer();
                }
              } else {
                MatthewsNamespace::BoomBox::IS_MUSIC_ENABLED = 1;
              }
            }
        } else if (Event->type == sf::Event::KeyPressed) {
          if (Event->key.code == sf::Keyboard::Escape) {  // Exits on ESC pressed
            ITEM_HOLDER.getA()->close();
            BoomBox::WindowSoundEffect();
            BOOMBOX_INSTANCES = 0;
            break;
          }
        } else if (Event->type == sf::Event::TextEntered) {
          if (Event->text.unicode < 128) break;
        }
      }
      std::free(Event);
      MatthewsNamespace::BoomBox::DrawInsideMainWindow(ITEM_HOLDER.getA(), ITEM_HOLDER.getB(),
                                                       ITEM_HOLDER.getC());
    }
  }
  void MatthewsNamespace::BoomBox::DrawInsideMainWindow(sf::RenderWindow* WINDOW,
                                                        sf::Thread* WINTHREAD,
                                                        VirtualWindowClass* C) {
    WINDOW->clear(sf::Color::Red);
    WINDOW->draw(BackGround->SPRITE);
    WINDOW->draw(Speaker1.get()->SPRITE);  // The first Speaker
    WINDOW->draw(Speaker2.SPRITE);         // The second Speaker
    WINDOW->draw(SoundBox.SPRITE);         // The box for sound
    WINDOW->draw(MusicBox.SPRITE);         // The box for music

    WINDOW->draw(SoundToggleText);
    WINDOW->draw(MusicToggleText);
    RenderLinesInCurrentFrame(WINDOW, 1);
    WINDOW->display();
  }
  void MatthewsNamespace::BoomBox::RenderTextures(
      DoubleItemHolder<sf::RenderWindow, VirtualWindowClass> ITEM_HOLDER) {
    // Inside a separate thread -> Background
    BackGround = std::make_unique<ImageToBeDrawn>();
    BackGround->TEXTURE.loadFromFile("RetroSpeakers.jpg");
    BackGround->SPRITE.setTexture(BackGround->TEXTURE);
    BackGround->SPRITE.setScale(1.5, 1.5);

    Speaker1 = std::make_unique<ImageToBeDrawn>();
    Speaker1->TEXTURE.loadFromFile("Speaker.png");
    Speaker1->SPRITE.setTexture(Speaker1->TEXTURE);
    Speaker1->SPRITE.setScale(0.1, 0.1);
    Speaker1->SPRITE.setPosition(ITEM_HOLDER.getA()->getSize().x / 2 - 250,
                                 ITEM_HOLDER.getA()->getSize().y / 2 - 100);

    Speaker2.SPRITE.setTexture(Speaker1->TEXTURE);
    Speaker2.SPRITE.setScale(0.1, 0.1);
    Speaker2.SPRITE.setPosition(ITEM_HOLDER.getA()->getSize().x / 2,
                                ITEM_HOLDER.getA()->getSize().y / 2 - 100);

    // Sound Toggle
    SoundBox.TEXTURE.loadFromFile("Rounded-Button.png");
    SoundBox.SPRITE.setTexture(SoundBox.TEXTURE);
    SoundBox.SPRITE.setPosition(WWidth / 4 - 25, -75);
    SoundBox.SPRITE.setScale(0.5, 0.5);

    // Music Toggle
    MusicBox.TEXTURE.loadFromFile("Rounded-Button.png");
    MusicBox.SPRITE.setTexture(MusicBox.TEXTURE);
    MusicBox.SPRITE.setPosition(WWidth / 4 - 25, WHeight / 2);
    MusicBox.SPRITE.setScale(0.5, 0.5);

    // Render Font for text
    GlobalWindowFont.loadFromFile("Fonts/Emulogic.ttf");
    SoundToggleText.setFont(GlobalWindowFont);
    SoundToggleText.setString("Sound Toggle");
    SoundToggleText.setCharacterSize(15);
    SoundToggleText.setFillColor(sf::Color::Blue);
    SoundToggleText.setStyle(sf::Text::Bold);
    SoundToggleText.setPosition(WWidth / 4 + 30, WHeight / 1.3);

    MusicToggleText.setFont(GlobalWindowFont);
    MusicToggleText.setString("Music Toggle");
    MusicToggleText.setCharacterSize(15);
    MusicToggleText.setFillColor(sf::Color::Blue);
    MusicToggleText.setStyle(sf::Text::Bold);
    MusicToggleText.setPosition(WWidth / 4 + 30, WHeight / 8);
  }

  // Other methods that are not overriden

  // Static functions -> The boombox can be accessed from anywhere
  void BoomBox::LoadAudioInMemory() {
    LocalDJ->ShootSoundBuffer.loadFromFile("BoomBoxRes/EnemyShoot.wav");  // Enemy shoot
    LocalDJ->ShootSound.setBuffer(LocalDJ->ShootSoundBuffer);
    LocalDJ->PShootSoundBuffer.loadFromFile("BoomBoxRes/PlayerShoot.wav");  // Player shoot
    LocalDJ->PShootSound.setBuffer(LocalDJ->PShootSoundBuffer);
    LocalDJ->WindowSoundBuffer.loadFromFile("BoomBoxRes/WindowEffect.wav");  // Window effect
    LocalDJ->WindowSound.setBuffer(LocalDJ->WindowSoundBuffer);
    LocalDJ->CollisionSoundBuffer.loadFromFile(
        "BoomBoxRes/CollisionEffect.wav");  // Collision effect
    LocalDJ->CollisionSound.setBuffer(LocalDJ->CollisionSoundBuffer);
    LocalDJ->WrongSelectionSoundBuffer.loadFromFile(
        "BoomBoxRes/WrongSelection.wav");  // Wrong window selection effect
    LocalDJ->WrongSelectionSound.setBuffer(LocalDJ->WrongSelectionSoundBuffer);
    LocalDJ->DeathSoundBuffer.loadFromFile("BoomBoxRes/GameOverSound.wav");  // Game over effect
    LocalDJ->DeathSound.setBuffer(LocalDJ->DeathSoundBuffer);
    LocalDJ->WelcomeSoundBuffer.loadFromFile("BoomBoxRes/GameStart.wav");  // Welcome effect
    LocalDJ->WelcomeSound.setBuffer(LocalDJ->WelcomeSoundBuffer);
    LocalDJ->UpgradeSoundBuffer.loadFromFile("BoomBoxRes/GameStart.wav");  // Upgrade effect
    LocalDJ->UpgradeSound.setBuffer(LocalDJ->UpgradeSoundBuffer);
    LocalDJ->EvilSoundBuffer.loadFromFile("BoomBoxRes/EvilEffect.wav");  // Upgrade effect
    LocalDJ->EvilSound.setBuffer(LocalDJ->EvilSoundBuffer);
  }
  void BoomBox::ShootSoundEffect() {  // Effects
    if (IS_SOUND_ENABLED) LocalDJ->ShootSound.play();
  }
  void BoomBox::PShootSoundEffect() {  // Effects
    if (IS_SOUND_ENABLED) LocalDJ->PShootSound.play();
  }
  void BoomBox::WindowSoundEffect() {  // Effects
    if (IS_SOUND_ENABLED) LocalDJ->WindowSound.play();
  }
  void BoomBox::WindowCollisionEffect() {  // Effects
    if (IS_SOUND_ENABLED) LocalDJ->CollisionSound.play();
  }
  void BoomBox::WrongSelectionEffect() {  // Effects
    if (IS_SOUND_ENABLED) LocalDJ->WrongSelectionSound.play();
  }
  void BoomBox::GameOverEffect() {  // Effects
    if (IS_SOUND_ENABLED) LocalDJ->DeathSound.play();
  }
  void BoomBox::WelcomeEffect() {  // Effects
    if (IS_SOUND_ENABLED) LocalDJ->WelcomeSound.play();
  }
  void BoomBox::UpgradeEffect() {  // Effects
    if (IS_SOUND_ENABLED) LocalDJ->UpgradeSound.play();
  }
  void BoomBox::EvilEffect() {
    if (IS_SOUND_ENABLED) LocalDJ->EvilSound.play();
  }

  void BoomBox::StartMainThemeSong() {  // Main Theme
    if (IS_MUSIC_ENABLED) {
      LocalDJ->MainThemeSoundBuffer.loadFromFile("Music/WelcomeMusic.wav");  // Music effect
      LocalDJ->MainThemeSound.setBuffer(LocalDJ->MainThemeSoundBuffer);
      BoomBox::getMainTheme()->play();
      BoomBox::getMainTheme()->setLoop(true);
    }
  }
  sf::Sound* BoomBox::getMainTheme() { return &LocalDJ->MainThemeSound; }

  // For the AnimationWindow BoomBox
  void BoomBox::LoadFileNameVector() {
    std::string path = "./Music";
    for (const auto& entry : fs::directory_iterator(path)) {
      std::string path_string{entry.path().u8string()};
      if (strstr(path_string.c_str(), ".wav") != NULL
          && strstr(path_string.c_str(), "WelcomeMusic.wav") == NULL) {
        WavFilesFromDirectory.push_back(
            path_string);  // Outputs the .wav files in the current directory
      }
    }
  }
  void BoomBox::INIT_BOOMBOX_MAIN() {
    LoadAudioInMemory();
    StartMainThemeSong();
    LoadFileNameVector();
  }
  std::optional<std::string>
  BoomBox::RandomSongGenerator() {  // Is going to generate a random song name at every call
    if (WavFilesFromDirectory.size() > 0 && IS_MUSIC_ENABLED) {
      int choice = RandomParticlesGenerator::Mersenne_Twister_Generator(
          0, WavFilesFromDirectory.size() - 1);
      LocalDJ->SOUND_MAIN_BUFFER.loadFromFile(WavFilesFromDirectory.at(choice));
      LocalDJ->SOUND_MAIN.setBuffer(LocalDJ->SOUND_MAIN_BUFFER);
      LocalDJ->SOUND_MAIN.play();
      return WavFilesFromDirectory.at(choice);
    }
    return {};
  }
  // Render WAV sine wave inside the BoomBox
  void BoomBox::RenderLinesInCurrentFrame(sf::RenderWindow* BoomBoxWindow, int precision) {
    // Render the lines for MainTheme if it is playing
    if (IS_MUSIC_ENABLED) {
      try {  // The song might have been deleted in another thread
        if (BoomBox::getMainTheme()->getStatus() == sf::SoundSource::Status::Playing) {
          // Get the current position
          sf::Time CurrentPosition = BoomBox::getMainTheme()->getPlayingOffset();
          // We need to do the math to get the current samples to be displayed
          // Freeze the thread until samples are available
          // while(CurrentPosition.asSeconds()==0){}
          if (BoomBox::getMainTheme()->getBuffer() != nullptr
              || BoomBox::getMainTheme()->getBuffer() != NULL) {
            const sf::Int16* LocalBuffer = BoomBox::getMainTheme()->getBuffer()->getSamples();
            int CurrentPosInSamples
                = CurrentPosition.asMilliseconds()
                  * BoomBox::getMainTheme()->getBuffer()->getSampleCount()
                  / BoomBox::getMainTheme()->getBuffer()->getDuration().asMilliseconds();

            // Build a vector of Lines
            for (int i{}; i < BoomBoxWindow->getSize().y; i += precision) {
              if (CurrentPosInSamples + i - 3 >= 0 && CurrentPosInSamples + i - 2 >= 0
                  && CurrentPosInSamples + i - 1 >= 0 && CurrentPosInSamples + i >= 0
                  && CurrentPosInSamples + i
                         < BoomBox::getMainTheme()->getBuffer()->getSampleCount()) {
                sf::VertexArray Vertex(sf::LinesStrip, 2);
                
                Vertex[0].position = sf::Vector2f(i, LocalBuffer[CurrentPosInSamples + i - 2] / 200
                                                         + BoomBoxWindow->getSize().y / 2);
                Vertex[1].position = sf::Vector2f(i + 1, LocalBuffer[CurrentPosInSamples + i] / 200
                                                             + BoomBoxWindow->getSize().y / 2);

                Vertex[0].color = sf::Color::Green;
                Vertex[1].color = sf::Color::Green;
                BoomBoxWindow->draw(Vertex);
              }
            }
          }
        }
        if (LocalDJ->SOUND_MAIN.getStatus() == sf::SoundSource::Status::Playing) {
          // Get the current position
          sf::Time CurrentPosition = LocalDJ->SOUND_MAIN.getPlayingOffset();
          // We need to do the math to get the current samples to be displayed

          // Freeze the thread until samples are available
          // while(CurrentPosition.asSeconds()==0){}
          if (LocalDJ->SOUND_MAIN.getBuffer() != nullptr
              || LocalDJ->SOUND_MAIN.getBuffer() != NULL) {
            const sf::Int16* LocalBuffer = LocalDJ->SOUND_MAIN.getBuffer()->getSamples();

            int CurrentPosInSamples
                = CurrentPosition.asMilliseconds()
                  * LocalDJ->SOUND_MAIN.getBuffer()->getSampleCount()
                  / LocalDJ->SOUND_MAIN.getBuffer()->getDuration().asMilliseconds();

            // Build a vector of Lines
            for (int i{}; i < BoomBoxWindow->getSize().y; i += precision) {
              if (CurrentPosInSamples + i - 3 >= 0 && CurrentPosInSamples + i - 2 >= 0
                  && CurrentPosInSamples + i - 1 >= 0 && CurrentPosInSamples + i >= 0
                  && CurrentPosInSamples + i < LocalDJ->SOUND_MAIN.getBuffer()->getSampleCount()) {
                sf::VertexArray Vertex(sf::LinesStrip, 2);
                // Vertex[0].position = sf::Vector2f(LocalBuffer[CurrentPosInSamples + i - 3] / 100,
                // LocalBuffer[CurrentPosInSamples + i - 2] / 100 + BoomBoxWindow->getSize().y/2);
                // Vertex[1].position = sf::Vector2f(LocalBuffer[CurrentPosInSamples + i - 1]/100,
                // LocalBuffer[CurrentPosInSamples + i]/100+ BoomBoxWindow->getSize().y / 2);
                Vertex[0].position = sf::Vector2f(i, LocalBuffer[CurrentPosInSamples + i - 2] / 200
                                                         + BoomBoxWindow->getSize().y / 2);
                Vertex[1].position = sf::Vector2f(i + 1, LocalBuffer[CurrentPosInSamples + i] / 200
                                                             + BoomBoxWindow->getSize().y / 2);

                Vertex[0].color = sf::Color::Green;
                Vertex[1].color = sf::Color::Green;
                BoomBoxWindow->draw(Vertex);
              }
            }
          }
        }
      } catch (std::exception E) {
      }
    }
  }
}  // namespace MatthewsNamespace