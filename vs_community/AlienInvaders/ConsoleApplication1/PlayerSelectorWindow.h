// Create a player selector window that loads a player with the selected spaceship and name
// Create a qmainapplication and a qmainwindow and set the mainwindow as the central widget

#include <qt5/QtWidgets/QMainWindow>
#include <qt5/QtWidgets/QApplication>
#include <qt5/QtCore/QString>

class MainWindow : public QMainWindow {
public:
  MainWindow(QWidget *parent = 0);  // Constructor
  // Create a function that will update the window with the new player information
  void updatePlayerInfo(QString name, QString ship);
  // Create a function that will update the window with the new player information
  void updatePlayerInfo(QString name, QString ship, int score);
  // Create a function that will update the window with the new player information
  void updatePlayerInfo(QString name, QString ship, int score, int lives);
};