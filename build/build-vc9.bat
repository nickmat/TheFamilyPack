bakefile -f msvs2008prj -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=vc9 -o vc9/tfp tfp.bkl

@echo off
if '%1' == 'cont' goto end
pause
:end
echo on
