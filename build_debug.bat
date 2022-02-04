:: Batch to build app

cmake -S standalone -B build/standalone
cmake --build build/standalone --config Debug

:: Copy everything from res (Assuming we use VSCommunity)
Xcopy /E /Icopy .\res\* .\build\standalone\Release\

:: Assuming we use other build systems
:: Xcopy /E /I .\res\* .\build\standalone\