bakefile -f gnu -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=gnu -o gnu/makefile tfp.bkl -DNO_UTILS=1 -DNO_DEPS

@echo off
if '%1' == 'cont' goto end
pause
:end
echo on
