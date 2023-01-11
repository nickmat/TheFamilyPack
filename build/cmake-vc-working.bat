rem Create or update vc-working CMake build sys

if not exist vc-working md vc-working
cd vc-working
cmake -G "Visual Studio 17 2022" ../../..

pause
