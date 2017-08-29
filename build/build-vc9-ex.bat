bakefile -f msvs2008prj -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=vc9-ex -o vc9-ex/tfp tfp.bkl -D INC_NON_SVN=1

@echo off
if '%1' == 'cont' goto end
pause
:end
echo on
