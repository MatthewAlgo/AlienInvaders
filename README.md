Do you remember those days when time passed very quickly when you played games like Chicken Invaders? It's time to bring those days back with AlienInvasionRetro! Embark on the ship and try to shoot down as many aliens as possible. Be careful, though, because they become more and more dangerous!

# Batch to build app
# For Linux

cmake -S standalone -B build/standalone \
cmake --build build/standalone --config Release
cmake --build build/standalone --config Release \ 
(Or just run the build_release.sh script) \
Install required dependencies if CMake throws errors \
Wait for the build... \
Copy everything from the "res" folder to "build/standalone" \
Run "build/standalone/AlienInvadersRetro" \
Have Fun!


# For Windows

cmake -S standalone -B build/standalone \
cmake --build build/standalone --config Release \ 
(Or just run the build_release.bat script) \
Install required dependencies if CMake throws errors \
Wait for the build... \
Copy everything from the "res" folder to "build/standalone" \
Run "build/standalone/AlienInvadersRetro" \
Have Fun!