bakefile -f msvc -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=nmake -o nmake/tfp.mak tfp.bkl -DNO_DEPS=1

@echo off
if '%1' == 'cont' goto end
pause
:end
echo on
