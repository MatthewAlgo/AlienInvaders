# For Linux

cmake -S standalone -B build/standalone \
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