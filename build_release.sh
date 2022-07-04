
# Batch to build app

:: Batch to build Executable

cmake -S main_sources -B build/main_sources
cmake --build build/main_sources --config Release


# Copy everything from res
cp -r ./res/* ./build/main_sources/
