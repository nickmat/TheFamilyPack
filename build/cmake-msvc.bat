rem Create or update msvc CMake build sys

if not exist msvc md msvc
cd msvc
cmake -G "Visual Studio 17 2022" ../..

pause
