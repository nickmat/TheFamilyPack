rem Create or update msvc CMake build sys

if not exist msvc-ex md msvc-ex
cd msvc-ex
cmake -G "Visual Studio 17 2022" ../../..

pause
