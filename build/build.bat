@echo off

if '%1'=='-h' goto usage
if '%1'=='?' goto usage
if '%1'=='' goto usage
if '%2'=='' goto nobuilddir
@echo on
bakefile -f %1 -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=%2 -o %2/tfp.mak tfp.bkl
@echo off
goto done

:nobuilddir
@echo on
bakefile -f %1 -I %WXWIN%\build\bakefiles\wxpresets -o tfp tfp.bkl
@echo off
goto done

:usage
echo usage:-
echo          build [format [build-dir]]
echo.
echo format   One of Bakefile's format codes
echo build-dir  A single level of subdirectory to place Bakefile's output files
echo.
echo example:-
echo   build msvs2008prj vc9
echo,

:done
