bakefile -f msvc -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=nmake-dep -o nmake-dep/tfp.mak tfp.bkl

@echo off
if '%1' == 'cont' goto end
pause
:end
echo on
