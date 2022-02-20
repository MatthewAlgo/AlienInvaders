#!/bin/sh

# Add SFML
sudo apt-get update
yes Y | sudo apt-get install libsfml-dev 

# SFML Dependencies
yes Y | sudo apt-get install libpthread-stubs0-dev
yes Y | sudo apt-get install libgl1-mesa-dev
yes Y | sudo apt-get install libx11-dev
yes Y | sudo apt-get install libxrandr-dev
yes Y | sudo apt-get install libfreetype6-dev
yes Y | sudo apt-get install libglew1.5-dev
yes Y | sudo apt-get install libjpeg8-dev
yes Y | sudo apt-get install libsndfile1-dev
yes Y | sudo apt-get install libopenal-dev

# Joystick
yes Y | sudo apt-get install libudev-dev

# Compiler and build Tool
yes Y | sudo apt-get install gcc vim git wget


# Install CMake 
wget https://github.com/Kitware/CMake/releases/download/v3.23.0-rc1/cmake-3.23.0-rc1-linux-x86_64.sh
bash cmake-3.23.0-rc1-linux-x86_64.sh


# Clone the game from Github 
git clone https://github.com/MatthewAlgo/AlienInvadersRetroBuild.git
# Build and run
cd AlienInvadersRetroBuild && ../cmake-3.23.0-rc1-linux-x86_64/bin/cmake -S standalone -B build/standalone && \
  ../cmake-3.23.0-rc1-linux-x86_64/bin/cmake --build build/standalone --config Release \
  && ./build/standalone/AlienInvadersRetroBuild