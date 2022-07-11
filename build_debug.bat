:: Batch to build Libraries

:: cmake -S main_libraries -B build/main_libraries
:: cmake --build build/main_libraries --config Debug

:: Copy everything from res (Assuming we use VSCommunity)
:: Xcopy /E /I .\res\* .\build\main_libraries\Debug\


:: Batch to build Executable

cmake -S main_sources -B build/main_sources
cmake --build build/main_sources --config Debug

:: Copy everything from res (Assuming we use VSCommunity)
Xcopy /E /I .\res\* .\build\main_sources\Debug\