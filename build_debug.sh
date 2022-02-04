# Script to build app

cmake -S standalone -B build/standalone
cmake --build build/standalone

# Copy everything from res
cp -r ./res/* ./build/standalone/