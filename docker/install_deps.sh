#!/bin/sh

# Backup the current repository
mkdir ~/apt.back
cd ~/apt.back
sudo cp /etc/apt/sources.list ../apt.back/
sudo cp /etc/apt/sources.list.d/*list ../apt.back/
sudo apt-get update
cd -

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
yes Y | sudo apt-get install vim git wget


# Install CMake 
wget https://github.com/Kitware/CMake/releases/download/v3.23.0-rc1/cmake-3.23.0-rc1-linux-x86_64.sh
bash cmake-3.23.0-rc1-linux-x86_64.sh

# Install a Compiler
# wget http://ftp.de.debian.org/debian/pool/main/g/gcc-defaults/g++_8.3.0-1_amd64.deb
# yes Y | sudo dpkg -i g++_8.3.0-1_amd64.deb
yes Y | sudo apt --fix-broken install
yes Y | sudo add-apt-repository ppa:ubuntu-toolchain-r/test
yes Y | sudo apt-get update
yes Y | sudo apt install gcc-11 g++-11
# yes Y | sudo apt install clang-11 --install suggests

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 700 --slave /usr/bin/g++ g++ /usr/bin/g++-7
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 800 --slave /usr/bin/g++ g++ /usr/bin/g++-11

# Clone the game from Github 
git clone https://github.com/MatthewAlgo/AlienInvadersRetroBuild.git
# Build and run
cd AlienInvadersRetroBuild && ../cmake-3.23.0-rc1-linux-x86_64/bin/cmake -S standalone -B build/standalone && \
  ../cmake-3.23.0-rc1-linux-x86_64/bin/cmake --build build/standalone --config Release
# Copy the resources
cp -r ./res/* ./build/standalone/
echo "Done! Please run the program located at {PROJECT_ROOT}/build/standalone/AlienInvadersRetro"